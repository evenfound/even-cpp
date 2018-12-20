/** @brief Тo be called when you want to stop the timer */
function abortTimer(tid) { 
    clearInterval(tid);
}

+function ($) {
    var
            tidOfCounter = 0,   ///< Id counter of model timer observer 
            boffinRunning = false,
            boffinAccessible = false,
            oldButtonText,      ///< Save Old button text       
            oldButtonCss = {},  ///< Old button main css 
            oldCaptionText,
            processRun = function (phase_) {
                console.log("Process phase_ " + phase_);
                var request = $.ajax({
                    url: (!boffinRunning)? "/process/start": "/process/stop",
                    method: "POST",
                    data: {id: 'menuId'},
                    dataType: 'json',
                    sync: false
                });
                request.done(function (msg) {
                    console.log(msg);
                });
            },        
            aquireStatus = function () {
                console.log("Got status..");
                var num = Math.random() * (100000 - 1001000) + 1000000;
                $('#transact-per-sec').html(num.toFixed(2));
                var exposition = $.ajax({
                    url: "/process/exposition",
                    method: "POST",
                    data: {id: 'menuId'},
                    dataType: 'json',
                    sync: false,
                    error: function(jqXHR_, status_, errorThrown_) {}
                });
                exposition.done(function(msg) {
                    console.log(msg['process/exposition']);
                    var counter = 1;
                    var result = `<thead>
                            <tr>
                                <th scope="col">#</th>
                                <th scope="col">Parameter</th>
                                <th scope="col">Value</th>
                            </tr>
                        </thead>
                    </thead>
                    <tbody>`;
                    $.each(msg['process/exposition'], $.proxy(function (i, val) {
                        console.log($.type(val.value));
                        if (val.intro != 'Type object') {
                            if (val.visible) {
                                var precision = (val.value < 0.01)? 2: val.precision;
                                result += `<tr>
                                    <th scope="row">` + counter + `</th>
                                    <td>` + val.intro + `</td>
                                    <td>` + val.value.toFixed(precision) + `</td>
                                    </tr>`;
                                ++counter;
                            }
                        }
                    }, this));
                    result += `</tbody>`;
                    $('#jumbo-display').html(result);
                });
                var request = $.ajax({
                    url: "/process/status",
                    method: "POST",
                    data: {id: 'menuId'},
                    dataType: 'json',
                    sync: false,
                    error: function(jqXHR_, status_, errorThrown_) {
                        //console.log(jqXHR_ + " -> " + status_ + " -> " + errorThrown_);                        
                        if(status_ == "error") {
                            boffinAccessible = false;
                            boffinRunning = false;
                            $('#toggle-model').css({
                                backgroundColor: 'gray',
                                borderColor: 'lightgray',
                                boxShadow: '0 0 0 0.2rem rgba(100, 100, 100, 0.5)'
                            });
                            $('#simulation-caption h4').css({
                                display: 'none'
                            });
                        }
                    }
                });
                request.done(function (msg) {
                    boffinAccessible = true;
                    console.log(msg);
                    switch (msg.status) {
                        case "running":
                            {
                                $('#toggle-model').html("Stop");
                                $('#toggle-model').css({
                                    backgroundColor: '#ff0000',
                                    borderColor: '#ffaaaa',
                                    boxShadow: '0 0 0 0.2rem rgba(200, 100, 100, 0.5)'
                                });
                                if (!$('#toggle-model').is(":visible"))
                                    $('#toggle-model').show();
                                $('#simulation-caption h4').html("running");
                                $('#simulation-caption h4').css({
                                    color: '#ff0000'
                                });
                                if (!$('#simulation-caption h4').is(":visible")) 
                                    $('#simulation-caption h4').show();
                                boffinRunning = true;
                            }
                            break;
                        case "stopped":
                            {
                                $('#toggle-model').html(oldButtonText);
                                $('#toggle-model').css({
                                    backgroundColor: oldButtonCss.backgroundColor,
                                    borderColor: oldButtonCss.borderColor,
                                    boxShadow: oldButtonCss.boxShadow
                                });
                                if (!$('#toggle-model').is(":visible"))
                                    $('#toggle-model').show();
                                $('#simulation-caption h4').html("stopped");
                                $('#simulation-caption h4').css({
                                    color: 'black'
                                });
                                if (!$('#simulation-caption h4').is(":visible")) 
                                    $('#simulation-caption h4').show();                                
                                boffinRunning = false;
                            }
                            break;
                    }
                });
            },
            initOnLoad = function () {
                oldButtonCss.backgroundColor = $('#toggle-model').css('background-color');
                oldButtonCss.borderColor = $('#toggle-model').css('border-color');
                oldButtonCss.boxShadow = $('#toggle-model').css('box-shadow');
                oldButtonText = $('#toggle-model').text();
                tidOfCounter = setInterval(aquireStatus, 500);
                $('#toggle-model').click($.proxy(function () {
                    if (!boffinAccessible)
                        return;
                    processRun(!boffinRunning);
                }, this));
                $('#simulation-caption h4').click($.proxy(function () {
                    if (!boffinAccessible)
                        return;
                    processRun(!boffinRunning);
                }, this));
            };
        
    $('body').ready(function () {
        initOnLoad();
    });

}(jQuery);