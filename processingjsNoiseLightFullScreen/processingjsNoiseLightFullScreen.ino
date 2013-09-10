/*
 Interaction with processing.js: a noise field that 
 changes radius size based on the value read from analog 
 pin A0.
 The html page is located into the "www" folder of this 
 sketch. Open the sketch folder from the top menu: 
 Sketch->Show Sketch Folder
   
 You can then go to http://arduino.local/sd/processingNoiseLightFullScreen
 to see the output of this sketch, where "arduino" is your 
 board name. 	

 08/2013 - Matteo Loglio (matlo.me) 	  
 */
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 

YunServer server;
String startString;

void setup() {
  server.listenOnLocalhost();
  Bridge.begin();
  server.begin();
}

void loop() {

  YunClient client = server.accept();

  if (client) {
    String command = client.readString();
    command.trim();

    if (command == "light") {

      int sensorValue = analogRead(A1);

      client.println("Status:200");
      client.println("content-type:application/json");
      client.println();
      client.print("{ \"sensorValue\":");
      client.print(sensorValue);
      client.println("}");      
    }

    client.stop();
  }
}




