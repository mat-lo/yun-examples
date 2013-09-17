//voice stuff
meSpeak.loadConfig("mespeak_config.json");
meSpeak.loadVoice("voices/en/en.json");

//load voice

function loadVoice(id) {
  var fname = "voices/" + id + ".json";
  meSpeak.loadVoice(fname, voiceLoaded);
}

//speakNow("hey dude") and your browser will say "hey dude"
speakNow = function(content) {
  meSpeak.speak(content, {
    amplitude: 100,
    wordgap: 5,
    pitch: 40,
    speed: 135
  });
};

//zepto · jQuery stuff
$(document).ready(function() {
  $('#magical-ride').click(function() {
    if (isWorking == false) {
      isWorking = true;
      startTheMagicalRide();
    }
  });
});

//Magical Ride!
var step = 0;
var pin = 0;
var isAnalog = false;
var mode = '';
var value = 0;
var blinduinoIsStillLookin = true;
var isWorking = false;
var intervalID;

function setStep(n) {
  step = n;
}

//after clicking, the magical ride begins

function startTheMagicalRide() {
  $('#magical-text').text("Blinduino is working");
  speakNow("Select an Arduino pin by saying its number in the microphone");
  startButton(event);
}

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
    showInfo('info_speak_now');
    //start_img.src = 'mic-animate.gif';
  };

  recognition.onerror = function(event) {
    if (event.error == 'no-speech') {
      //start_img.src = 'mic.gif';
      showInfo('info_no_speech');
      ignore_onend = true;
    }
    if (event.error == 'audio-capture') {
      //start_img.src = 'mic.gif';
      showInfo('info_no_microphone');
      ignore_onend = true;
    }
    if (event.error == 'not-allowed') {
      if (event.timeStamp - start_timestamp < 100) {
        showInfo('info_blocked');
      } else {
        showInfo('info_denied');
      }
      ignore_onend = true;
    }
  };


  //when webSpeech gets results
  recognition.onresult = function(event) {

    for (var i = event.resultIndex; i < event.results.length; ++i) {
      result = event.results[i][0].transcript;
      //console.log(result);
      $('#magical-text').text(result);

      if (step == 0) {

        pin = Number(result);

        if (isNaN(pin)) {
          speakNow("that's not a number, say a pin number from 0 to 13");
        } else if (pin > 13) {
          speakNow("arduino has only 13 pins");
        } else {
          //is pin an analog ouptut?
          if (pin == 11 || pin == 10 || pin == 9 || pin == 6 || pin == 5 || pin == 3 || pin == 13) {
            isAnalog = true;
          }
          speakNow("you selected pin number" + pin + ". Say how do you want to use it. Just say input or output");
          step++;
        }
      } else if (step == 1) {

        mode = result;

        if (mode == ' output') {
          $.get('/arduino/mode/' + pin + '/output', function() {});
          speakNow("pin number" + pin + "is set to" + mode);
          if (isAnalog) {
            setTimeout(function() {
              speakNow("pin" + pin + " is a PWM. Say a value from 0 to 255 to assign to that pin");
            }, 3000);
          } else {
            setTimeout(function() {
              speakNow("pin" + pin + " is a digital pin. To set it just say high or low");
            }, 3000);
          }
          step++;
        } else if (mode == ' input') {
          $.get('/arduino/mode/' + pin + '/input', function() {});

          if (pin <= 5 && pin > 0) {
            speakNow("pin A" + pin + "is set to analog input");
            setInterval(function() {
              refreshInput(pin);
              speakNow("pin " + pin + " is reading" + value + ". To cancel say banana");
            }, 6000);
          } else {
            speakNow("pin " + pin + "is set to digital input");
            intervalID = setInterval(function() {
              refreshInput(pin);
              var highlow = '';
              if (value > 512) {
                highlow = 'high'
              } else {
                highlow = 'low'
              }
              speakNow("pin " + pin + " is reading " + highlow + ". To cancel say banana");
            }, 6000);
          }
          step += 2;
        } else {
          speakNow("i couldn't recognize it, try again");
        }
      }

      //output
      else if (step == 2) {
        var valid = false;
        if (isAnalog) {

          if (result == ' banana') {
            restart();
            break;
          }

          value = Number(result);

          if (isNaN(value)) {
            speakNow("that's not a number. try again");
          } else if (value < 0 || value > 255) {
            speakNow("that's not under 255");
          } else {
            valid = true;
          }
        } else {
          if (result == ' high') {
            value = 255;
            valid = true;
          } else if (result == ' low') {
            value = 0;
            valid = true;
          } else {
            speakNow("just say high or low");
          }
        }

        if (valid) {
          speakNow("pin" + pin + " set to " + result + ". Say another value to set it again or banana to start over");
          $.get('/arduino/analog/' + pin + '/' + value, function() {});
        }
      }

      //input 
      else if (step == 3) {
        if (result == ' banana') {
          restart();
          break;
        }
      }
    }
  };
}

//read json from yunServer

function refreshInput(_pin) {
  $.get('/arduino/analog/' + _pin, function(json_response) {
    value = json_response.pinValue;
  });
}

//start over

function restart() {
  step = 0;
  isWorking = false;
  welcomeDude();
  clearInterval(intervalID);
}

//opening scene

function welcomeDude() {
  speakNow("Welcome to Blinduino. Click anywhere to start");
  setTimeout(function() {
    $('#magical-text').text("Click anywhere to start");
  }, 4000);
}

//event that fires up the voice rec. If the page is https,
//it's enough to give permission to use the mic just once. 
//If you're working with blind people you want this feature enabled.

function startButton(event) {
  if (recognizing) {
    recognition.stop();
    return;
  }
  final_transcript = '';
  recognition.lang = 'en-GB', 'United Kingdom';
  recognition.start();
  ignore_onend = false;
  //start_img.src = 'mic-slash.gif';
  //showInfo('info_allow');
  showButtons('none');
  start_timestamp = event.timeStamp;
}