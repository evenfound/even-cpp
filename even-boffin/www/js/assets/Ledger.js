+function ($) {
    $('body').ready(function () {
        var request = $.ajax({
            url: "/process/lookupshared",
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