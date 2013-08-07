/* 
 Use an HTML control panel to visualize
 input values from analog pins. The html page is located
 into the "www" folder of this sketch. Open the sketch
 folder from the top menu: Sketch->Show Sketch Folder

 You can then go to http://arduino.local/sd/analogInputs
 to see the output of this sketch, where "arduino" is your 
 board name. 	 
*/

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 


YunServer server;
String startString;

void setup() {
  //initialize bridge
  Bridge.begin();
  
  //start local server
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  
  YunClient client = server.accept();

  if (client) {
    String command = client.readString();
    command.trim();
    if (command == "inputs") {

      int lightVal = analogRead(A0);
      
      //init JSON data
      client.println("Status:200");
      client.println("content-type:application/json");
      client.println();
      client.println("{");
      
      /*
      loop through the analog pins and for each pin,
      make a JSON line, like:
      "A0" : 450
      */
      for(int i = 0; i <= 5; i++) {        
        client.print("\"A");
        client.print(i);
        client.print("\":");        
        if (i == 5) {
          client.println(analogRead(i));
        } 
        else {
          client.print(analogRead(i));
          client.println(",");
        }
      }
      
      //close
      client.println("}");     
    }


    client.stop();
  }

  delay(50); // Poll every 50ms
}









