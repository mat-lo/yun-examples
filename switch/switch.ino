/*
 to visit the html page, go in your browser and type:
 http://arduino.local/sd/switch
 where "arduino" is your board name, after uploading 	
 the sketch via WiFi.
 
 On the web page, there's a switch that triggers
 a TinkerKit! Relay and the LED 13 on the board
 
 10/13 - Matteo Loglio (matlo.me)
 */

#include <TinkerKit.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;

TKRelay relay(O0);

void setup() {
  Serial.begin(9600);

  // Bridge startup
  pinMode(13,OUTPUT);
  Bridge.begin();

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {

    String command = client.readStringUntil('/');

    // is "relay" command?
    if (command == "relay") {

      int stat = client.parseInt();

      if (stat == 1) {
        digitalWrite(13, HIGH);
        relay.on();      
      } 
      else {
        digitalWrite(13, LOW);
        relay.off();
      }
    }

    // Close connection and free resources.
    client.stop();
  }

  delay(50); // Poll every 50ms
}


