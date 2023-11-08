#if DEBUG_SERIAL == TRUE

/* IO Tests ---------------------------------------------- */
void testDecoder() {
  for (int i = 0; i < 4; i += 1) {
    Serial.print("Decoder ");
    Serial.println(i);
    setDecoder(i);
    delay(1000);
  }
}

void testAnalog(){
    Serial.print(" A2=");
    Serial.print(analogRead(A2));
    Serial.print(" A3=");
    Serial.println(analogRead(A3));
}

void testUltrasonic() {
  Serial.print("distance(cm) = ");
  Serial.println(ultrasonic());
  delay(500);
}

/* Colour ---------------------------------------------------------------------------------------- */



void testPrint(int n, char *arrayName, float array[]) {
  Serial.print("float ");
  Serial.print(arrayName);
  Serial.print("[] = {");
  for(int c = 0; c < n; c++){  
      if (c != 0) {
        Serial.print(", ");
      }
      Serial.print(float(array[c]));
  }
  Serial.println("};");
}

void testCalibration(){
  setBalance();
  #ifdef DEBUG_SERIAL
    testPrint(NO_COLOURS, "whiteArray", whiteArray);
    testPrint(NO_COLOURS, "blackArray", blackArray);
    testPrint(NO_COLOURS, "greyDiff", greyDiff);
  #endif
}

void testColourReading() {
  float colourArray[] = {0,0,0};
  readColour(NO_COLOURS, colourArray);
  testPrint(NO_COLOURS, "colour", colourArray);
}

void testColourEnum() {
  int colourEnum = getColourEnum();
  Serial.print("Colour Enum: ");
  //serialPrintColour(colourEnum);
  Serial.println();
}
#endif