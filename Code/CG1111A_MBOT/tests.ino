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

char colourStr[3][5] = {"R = ", "G = ", "B = "};

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
  for(int c = 0; c < NO_COLOURS; c++){  
    #ifdef DEBUG_SERIAL
      Serial.print(colourStr[c]);
      Serial.println(int(colourArray[c])); //show the value for the current colour LED, which corresponds to either the R, G or B of the RGB code
    #endif
  }
}

void testColourEnum() {
  int colourEnum = getColourEnum();
  Serial.print("Colour Enum: ");
  Serial.println(colourEnum);
}
#endif