(function($){
  
  $('body').ready(function(){
        var request = $.ajax({
            url: "/boffin",
            method: "POST",
            data: {id: 'menuId'},
            dataType: 'json'
        });
 
        request.done(function (msg) {
            //$("#log").html(msg);
            console.log(msg);
        });
      
  });
   
})(jQuery);