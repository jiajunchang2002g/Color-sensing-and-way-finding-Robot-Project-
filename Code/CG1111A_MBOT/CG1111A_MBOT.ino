#include <MeMCore.h>
#include "config.h"

void setup() {
 // Any setup code here runs only once:
  initDecoder();
  #ifdef DEBUG_SERIAL
    Serial.begin(9600);
  #endif
}

void loop() {
  // testDecoder();
  testAnalog();
  // testCalibration();
  //testColourReading();
}