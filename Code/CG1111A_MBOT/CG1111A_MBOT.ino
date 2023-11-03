#include <MeMCore.h>
#include "config.h"

void setup() {
 // Any setup code here runs only once:
  initDecoder();
  pinMode(A7,INPUT); // init button
  #ifdef DEBUG_SERIAL
    Serial.begin(9600);
  #endif
  Serial.println("test");
  
  
  //wallFollower(); 
}

void loop() {
  while (analogRead(A7) > 10){}
  mainLoopLogic();
  // testDecoder();
  // testAnalog();

  // Calibration
  //testCalibration();
  //testColourReading();
  //testColourEnum();

  //wallFollower();
}