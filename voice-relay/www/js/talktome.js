//Voice Recognition 
var final_transcript = '';
var recognizing = false;
var ignore_onend;
var start_timestamp;

if (!('webkitSpeechRecognition' in window)) {
  upgrade();
} else {
  //start_button.style.display = 'inline-block';
  var recognition = new webkitSpeechRecognition();
  recognition.continuous = true;
  recognition.interimResults = false;

  recognition.onstart = function() {
    recognizing = true;
    //showInfo('info_speak_now');
    //start_img.src = 'mic-animate.gif';
  };

  recognition.onerror = function(event) {
    if (event.error == 'no-speech') {
      //start_img.src = 'mic.gif';
      //showInfo('info_no_speech');
      ignore_onend = true;
    }
    if (event.error == 'audio-capture') {
      //start_img.src = 'mic.gif';
      //showInfo('info_no_microphone');
      ignore_onend = true;
    }
    if (event.error == 'not-allowed') {
      if (event.timeStamp - start_timestamp < 100) {
        //showInfo('info_blocked');
      } else {
        //showInfo('info_denied');
      }
      ignore_onend = true;
    }
  };


  //when webSpeech gets results
  recognition.onresult = function(event) {
    for (var i = event.resultIndex; i < event.results.length; ++i) {
      result = event.results[i][0].transcript;
      //console.log(result);
      $('#magical-text').text("\"" + result + "\"");
      

      if (result == "off" || result == " off") {
        relayOff();
        if(recognizing) {
          $('#start-button').toggleClass("inactive");
          $('#start-button').toggleClass("active");
          startButton();
        }
      } 

      if (result == "on" || result == " on") {
        relayOn();
        if(recognizing) {
          $('#start-button').toggleClass("inactive");
          $('#start-button').toggleClass("active");
          startButton();
        }
      } 
    }    
  };

  recognition.onend = function() {
    recognizing = false;
    
    $('#start-button').removeClass("active");
    $('#start-button').addClass("inactive");
          
  };
}

function visualStart() {

}

function visualStop() {
  
}

//read json from yunServer
function refreshInput() {
}

//event that fires up the voice rec. If the page is https,
//it's enough to give permission to use the mic just once. 
//If you're working with blind people you want this feature enabled.
function startButton(event) {  
  if (recognizing) {
    $('#magical-text').text("Silence");
    recognition.stop();
    return;
  }
  
  $('#magical-text').text("Listening...");

  final_transcript = '';
  recognition.lang = 'en-GB', 'United Kingdom';
  recognition.start();
  ignore_onend = true;
  //start_img.src = 'mic-slash.gif';
  ////showInfo('info_allow');
  //showButtons('none');  
}

function relayOn() {
  $('#checkbox1').prop('checked', true);
  $('#bulb').css("background-color","rgb(255,235,138)");

  //send to arduino
  $.get('/arduino/relay/1', function(){            
            }
          );
}

function relayOff() {
  $('#checkbox1').prop('checked', false);  
  $('#bulb').css("background-color","transparent");

  //send to arduino
  $.get('/arduino/relay/0', function(){            
            }
          );
}

$( document ).ready(function() {
  $('#start-button').click(function() {
    
    startButton(event);

    $(this).toggleClass("inactive");
    $(this).toggleClass("active");
  })

  $('#checkbox1').click(function() {
    var $this = $(this);
    // $this will contain a reference to the checkbox   
    if ($this.is(':checked')) {
        //ON
        relayOn();
    } else {
        //OFF
        relayOff();
    }
});
});
