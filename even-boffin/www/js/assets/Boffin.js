+function ($) {
    var
            showNetworkInfo = function (boffin) {
                var counter = 1;
                var result = `<table class="table table-striped"> 
                    <thead>
                        <tr>
                            <th>#</th>
                            <th>Intro</th>
                            <th>Value</th>
                        </tr>
                    </thead>
                    <tbody>`;
                $.each(boffin, $.proxy(function (i, val) {
                    //console.log($.type(val));
                    if ($.type(val) != 'array') {
                        result += `<tr>
                            <td style="width: 50px;">` + counter + `</td>
                            <td style="width: auto;">` + val.intro + `</td>
                            <td style="width: auto;">` + val.value + `</td>
                        </tr>`;
                        ++counter;
                    }
                }, this));
                result += `</tbody>
                </table>`;
                $(result).appendTo("#boffin-setup");
            };
    $('body').ready(function () {
        var request = $.ajax({
            url: "/network",
            method: "POST",
            data: {id: 'menuId'},
            dataType: 'json'
        });
        request.done(function (msg) {
            //$("#log").html(msg);
            showNetworkInfo(msg.network);
        });
    });
}(jQuery);