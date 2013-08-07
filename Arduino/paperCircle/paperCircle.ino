/* 
 Interaction with paper.js: a circle changes
 radius based on the value read from analog pin A0.
 The html page is located into the "www" folder of this 
 sketch. Open the sketch folder from the top menu: 
 Sketch->Show Sketch Folder
 
 You can then go to http://arduino.local/sd/paperCircle
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
    // read the command
    String command = client.readString();
    command.trim();        //kill whitespace
    Serial.println(command);
    // is "light" command?
    if (command == "light") {
      
      //we used a light sensor on A0
      int lightVal = analogRead(A0);
      
      //pack a JSON string, easier to parse
      client.println("Status:200");
      client.println("content-type:application/json");
      client.println();
      client.print("{ \"lightVal\":");
      client.print(lightVal / 3);
      client.println("}");      
    }

    // Close connection and free resources.
    client.stop();
  }

  delay(50); // Poll every 50ms
}






