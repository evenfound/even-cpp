+ function ($) {
var
        showNetworkInfo = function (boffin) {
        console.log(boffin);
                $(`<table class="table table-striped"> 
                    <thead>
                        <tr>
                            <th>#</th>
                            <th>Intro</th>
                            <th>Value</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td>1</td>
                            <td>` + boffin.object.intro +`</td>
                            <td>` + boffin.object.value +`</td>
                        </tr>
                        <tr>
                            <td>2</td>
                            <td>` + boffin.network_size.intro +`</td>
                            <td>` + boffin.network_size.value +`</td>
                        </tr>
                        <tr>
                            <td>3</td>
                            <td>` + boffin.proof_nodes.intro +`</td>
                            <td>` + boffin.proof_nodes.value +`</td>
                        </tr>
                        <tr>
                            <td>4</td>
                            <td>` + boffin.tick.intro +`</td>
                            <td>` + boffin.tick.value +`</td>
                        </tr>
                        <tr>
                            <td>5</td>
                            <td>` + boffin.path.intro +`</td>
                            <td>` + boffin.path.value +`</td>
                        </tr>
                    </tbody>
                </table>`).appendTo("#boffin-setup");
//                $.each(boffin.objects, function (index, value) {
//                    console.log(index + ": " + value);
//                });

        };
        $('body').ready(function () {
var request = $.ajax({
url: "/boffin",
        method: "POST",
        data: {id: 'menuId'},
        dataType: 'json'
});
        request.done(function (msg) {
        //$("#log").html(msg);
        showNetworkInfo(msg.boffin);
        });
        });
}(jQuery);