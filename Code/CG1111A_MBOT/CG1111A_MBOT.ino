#include <MeMCore.h>
#include "config.h"

void setup() {
 // Any setup code here runs only once:
  initDecoder();
  initLedButton();
  #ifdef DEBUG_SERIAL
    Serial.begin(9600);
  #endif
  Serial.println("test");
  
  
  //wallFollower(); 
}

void loop() {
  startOnButtonPress();
  mainLoopLogic();
  //testDecoder();
  // testAnalog();

  // Calibration
  //testCalibration();
  //testColourEnum();

  //wallFollower();
}