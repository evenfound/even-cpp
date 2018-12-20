+function ($) {
    var
            testNew = "Привет!";

    console.log(getUrlParameter("node"));
    $('body').ready(function () {
        var request = $.ajax({
            url: "/node/wallet/" + getUrlParameter("node"),
            method: "POST",
            data: {id: 'menuId'},
            dataType: 'json'
        });
        request.done(function (msg) {
            //$("#log").html(msg);
            console.log(msg);
        });
    });
}(jQuery);