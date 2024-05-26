//********************
// this is a simple example that uses the painlessMesh library
//
// 1. sends a silly message to every node on the mesh at a random time between 1 and 5 seconds
// 2. prints anything it receives to Serial.print
//
//
//********************
#include "painlessMesh.h"

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

#define pin_no1 12
#define pin_no2 13
#define pin_no3 14

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;


// User stub


// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.println( msg.c_str());
  int msgValue = atoi(msg.c_str());
  // Serial.println(PRINT_TYPE(msg.c_str()));
  if((msgValue==1)||(msgValue==3)||(msgValue==5)||(msgValue==7)){
      digitalWrite(pin_no1, LOW); 
      digitalWrite(pin_no2, LOW); 
      digitalWrite(pin_no3, LOW);
      Serial.println("Button pressed");
      delay(2000);
  }
  else{
      digitalWrite(pin_no1, HIGH); 
      digitalWrite(pin_no2, HIGH); 
      digitalWrite(pin_no3, HIGH);
      Serial.println("Button is not pressed");
      delay(20);
  }
  
}


void setup() {
  Serial.begin(9600);
  pinMode(pin_no1, OUTPUT);
  pinMode(pin_no2, OUTPUT);
  pinMode(pin_no3, OUTPUT);
  digitalWrite(pin_no1, HIGH); 
  digitalWrite(pin_no2, HIGH); 
  digitalWrite(pin_no3, HIGH);

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);

}

void loop() {
  // it will run the user scheduler as well
  mesh.update();
}