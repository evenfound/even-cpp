+ function ($) {
    var
            showNodes = function (boffin) {
                console.log(boffin);
                var sTable = `<table class="table table-striped"> 
                    <thead>
                        <tr>
                            <th style='width: 5%;'>#</th>
                            <th style='width: 10%;'>Balance</th>
                            <th style='width: 85%;'>Address</th>
                        </tr>
                    </thead>
                    <tbody>`;
                $.each(boffin.objects, function (index, value) {
                    console.log(index + ": " + value);
                    sTable += `<tr>
                            <td>` + (index + 1) + `</td>
                            <td>` + value.balance.value + `</td>
                            <td><a href='/wallet.html?node=` + value.hash.value +`' title='Wallet of node'>` + value.hash.value + `</a></td>
                        </tr>`;
                });
                sTable += `</tbody>
                </table>`;

                $(sTable).appendTo("#nodes");

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
            showNodes(msg.network);
        });
    });
}(jQuery);