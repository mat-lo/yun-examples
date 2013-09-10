var pin;
var intervID;

$(document).ready(function() {
  $('.progress').hide();
});

$('input:checkbox').change(function() {

      //IN
      if($(this).is(":checked")) {
        $('.progress').show();
        $('#slider').hide();
        $.get('/arduino/mode/' + pin + '/input', function(){}); 

        intervID = setInterval( refresh, 1000 );
       	
      } else {
        //OUT
        clearInterval(intervID);
        $('.progress').hide();
        $('#slider').show();
        $.get('/arduino/mode/' + pin + '/output', function(){});  
      }
    });
	
	function refresh() {

		$.get('/arduino/analog/' + pin, function(json_response){
		  				var value = json_response.pinValue;				  						  			
			  			setProgress(value);
			  		}
			  	);        
	}

	function setProgress(pinValue) {
		pinValue /= 4;
		var w = (pinValue * 100) / 255;        
        $("#pbar").css("width", w+"%");
	}
   // jQuery UI Sliders
    var $slider = $("#slider");
    
      $slider.slider({
        min: 1,
        max: 255,
        value: 120,
        orientation: "horizontal",
        range: "min"
      });

      
      $( "#slider" ).on( "slidechange", function( event, ui ) {      	
      	
        var val = $("#slider").slider( "value" );
        $.get('/arduino/analog/' + pin + '/' + val, function(){});      
        
      } );

      $( "select" ).change(function() {
         pin = $(this).val();         


         //check if analog input:
         if (isNaN(pin)) {
          
          intervID = setInterval( refresh, 1000 );
          
          $('#cb').hide();
          $('.progress').show();
          $('#slider').hide();


         } else {

          clearInterval(intervID);

          $('#cb').show();
          $('.progress').hide();
          $('#slider').hide();
         }


      });
