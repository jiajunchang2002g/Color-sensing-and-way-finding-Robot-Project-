#include <MeMCore.h>
#include "config.h"

void setup() {
  initDecoder();
  initLedButton();
  #ifdef DEBUG_SERIAL
    Serial.begin(9600);
    Serial.println("start");
  #endif
}

void loop() {
  startOnButtonPress();
  mainLoopLogic();

  /* Other Test functions - Uncomment to run */
  // testDecoder();
  // testAnalog();

  // Calibration
  // testCalibration();
  // testColourEnum();

  // wallFollower();
}