+ function ($) {
    var
            showNodes = function (boffin) {
                console.log(boffin);
                var sTable = `<table class="table table-striped"> 
                    <thead>
                        <tr>
                            <th>#</th>
                            <th>Balance</th>
                            <th>Address</th>
                        </tr>
                    </thead>
                    <tbody>`;
                $.each(boffin.objects, function (index, value) {
                    console.log(index + ": " + value);
                    sTable += `<tr>
                            <td>` + (index + 1) + `</td>
                            <td>` + value.balance.value + `</td>
                            <td><a href='/node/`+ index +`'>` + value.hash.value + `</a></td>
                        </tr>`;
                });
                sTable += `</tbody>
                </table>`;

                $(sTable).appendTo("#nodes");

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
            showNodes(msg.boffin);
        });
    });
}(jQuery);