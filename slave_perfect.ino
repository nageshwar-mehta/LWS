
#include "painlessMesh.h"

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;
#define pin_no 12
String on = "7";
String off = "8";
String prev_val = on;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  if(digitalRead(pin_no)==HIGH){
      mesh.sendBroadcast( on );
      prev_val = on;
  }
  else{
    if(prev_val == on){
      mesh.sendBroadcast(off);
      prev_val = off;
    }
  }
  
  taskSendMessage.setInterval( ( TASK_SECOND * 0.2));
}


void setup() {
  Serial.begin(9600);
  pinMode(pin_no, OUTPUT);
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() {
  // it will run the user scheduler as well
  mesh.update();
}