/*
 Interaction with three.js: a rotating box changes
 y-size based on the value read from analog pin A0.
 The html page is located into the "www" folder of this 
 sketch. Open the sketch folder from the top menu: 
 Sketch->Show Sketch Folder
   
 You can then go to http://arduino.local/sd/threejs
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
  Serial.begin(9600);
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
    String command = client.readString();
    command.trim();
    if (command == "light") {

      int lightVal = analogRead(A0);

      client.println("Status:200");
      client.println("content-type:application/json");
      client.println();
      client.print("{ \"lightVal\":");
      
      //light sensor values are too big,
      //divide them by 3
      client.print(lightVal / 3);
      client.println("}");      
    }

    client.stop();
  }

  delay(50); // Poll every 50ms
}





