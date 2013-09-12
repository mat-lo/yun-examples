#include <font_5x4.h>
#include <HT1632.h>
#include <images.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;
int x_pos = 0;
int curr_msg, last_msg;
int wd;
String msg[10];  //10 messages can be stored in the queue
char final_message[32];


void setup () {
  // Setup and begin the matrix
  // HT1632.begin(CS1,WR,DATA)
  HT1632.begin( 9, 10, 11);
  Serial.begin(9600);
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();  
  
  //************Set the standard message************
  msg[0] = "No MSG";
  msg[0].toCharArray(final_message,32);
  wd = HT1632.getTextWidth(final_message, FONT_5X4_WIDTH, FONT_5X4_HEIGHT); // Give the width, in columns, of the assigned string
  
  //************Set the buffer's variables*********
  curr_msg = 0;
  last_msg = 0;
}
 
void loop () {
  //*********Read new message from the server**************
  YunClient client = server.accept();
  
  if(client) {
    String command = client.readStringUntil('/');
    if (command == "msg") {      
      if (last_msg > 8 ) last_msg = 0;
      else last_msg++;
      msg[last_msg] = client.readStringUntil('/');            
    }
    client.stop();
    
  } 
  
  
  //*****Display the message on the matrix*****
  HT1632.drawTarget(BUFFER_BOARD(1));
  HT1632.clear();
  HT1632.drawText(final_message, 2*OUT_SIZE - x_pos, 2, FONT_5X4, FONT_5X4_WIDTH, FONT_5X4_HEIGHT, FONT_5X4_STEP_GLYPH);
  HT1632.render();
  
 
  
  //*************Move the message and select new messages*****************
  
  x_pos++;; //shift the message of 1 column to left
  
  //check if the the entire message goes out from the left edge
  if  (x_pos == (wd + OUT_SIZE * 2)) {  
    
    x_pos = 0;        //set the message position to the initial position
    
    if (curr_msg!=last_msg){         //is there an unread message?
    
      if (curr_msg < 9 ) curr_msg++;  //select the next message
      else curr_msg = 0;     //end of the buffer, start from beginning
      msg[curr_msg].toCharArray(final_message,32);   //convert the string into a char array
      wd = HT1632.getTextWidth(final_message, FONT_5X4_WIDTH, FONT_5X4_HEIGHT); // Give the width, in columns, of the assigned string
      
    }
  }
  
  delay(150);
}
