/* 
 HTML page with a custom color picker that controls an RGB led.
 The html page is located into the "www" folder of this sketch. 
 Open the sketch folder from the top menu: Sketch->Show Sketch Folder

 You can then go to http://arduino.local/sd/color_picker
 to see the output of this sketch, where "arduino" is your 
 board name. 	

 09/2013 - Matteo Loglio (matlo.me) 	   
*/
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 

YunServer server;
String startString;

//rgb led hooked up on pins 11,9 and 3
int r = 11;
int g = 9;
int b = 3;

void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop() {
  YunClient client = server.accept();

  if(client) {  
    String command = client.readStringUntil('/');    
    if (command == "rgb") {
      //received string is "r.g.b"
      //parseInt "consumes" the string
      analogWrite(r, client.parseInt());
      analogWrite(g, client.parseInt());
      analogWrite(b, client.parseInt());
    }    
    client.stop();
  }
}




