#include <MeMCore.h>

// Serial Config
#define DEBUG_SERIAL TRUE

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