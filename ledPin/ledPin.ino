/*
 Control a LED (or any analog output) connected to any
 PWM pin, using an html control panel with a
 drop-down to select the pin and a slider for the
 value (<input type="range" may not work
 in non-webkit browsers (firefox)).
 
 The html page is located into the "www" folder of this 
 sketch. Open the sketch folder from the top menu: 
 Sketch->Show Sketch Folder
   
 You can then go to http://arduino.local/sd/ledPin
 to see the output of this sketch, where "arduino" is your 
 board name. 	

 08/2013 - Matteo Loglio (matlo.me) 	  
*/
 
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;
String startString;

void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?  
  if(client) {  
    //readStringUntil() "consumes" the string.
    //this means that if command was led/20, now
    //it's just 20.
    String command = client.readStringUntil('/');    
    if (command == "led") {
      
      //also parseInt "consumes" the string
      int pin = client.parseInt();
      int value = client.parseInt();
      analogWrite(pin, value);
    }    
    client.stop();
  }
}


