/*
 * The calibration code is using the colour sensing code given in that respecitive lab as reference
 * Comments are kept (but formatted) to ensure clarity, since it is of a significant length
 * Changes are made to ensure that it works with our decoder setup
 */

int red = 0;
int green = 0;
int blue = 0;

int getAvgReading(int count){      
  int value = 0;
  for(int i = 1; i <= count; i++){
     value += analogRead(LDR);
     delay(LDRWait);
  }
  return value / count;
}

/* Calibration --------------------------------------------------------------------------------------------- */

void setBalance(){
  Serial.println("Put White Sample For Calibration ...");
  delay(5000);           // delay for five seconds for getting sample ready
  digitalWrite(LED,LOW); // Check Indicator OFF during Calibration
  // scan the white sample.
  // go through one colour at a time, set the maximum reading for each colour -- red, green and blue to the white array
  for(int i = 0;i<=2;i++){
    setDecoder(COLOUR_DEC_PIN[i]); // Turn on LED
    delay(RGBWait);
    whiteArray[i] = getAvgReading(5);  // scan 5 times and return the average,
  }
  // done scanning white, time for the black sample.
  // set black balance
  Serial.println("Put Black Sample For Calibration ...");
  delay(5000); // delay for five seconds for getting sample ready 

  // go through one colour at a time, set the minimum reading for red, green and blue to the black array
  for(int i = 0;i<=2;i++){
    setDecoder(COLOUR_DEC_PIN[i]); // Turn on LED
    delay(RGBWait);
    blackArray[i] = getAvgReading(5); // scan 5 times and return the average,
    // the differnce between the maximum and the minimum gives the range
    greyDiff[i] = whiteArray[i] - blackArray[i];
  }

  // delay another 5 seconds for getting ready colour objects
  Serial.println("Colour Sensor Is Ready.");
  delay(5000);
}

/* Reading value ----------------------------------------------------------------------------------------- */

void readColour(int noColours, float colourArray[]) {
  for(int c = 0; c <= noColours; c++){       
    // turn ON the LED, red, green or blue, one colour at a time.
    setDecoder(COLOUR_DEC_PIN[c]);
    delay(RGBWait);
    colourArray[c] = getAvgReading(5);

    /* 
     * the average reading returned minus the lowest value divided by the maximum possible range, 
     * multiplied by 255 will give a value between 0-255, 
     * representing the value for the current reflectivity (i.e. the colour LDR is exposed to)
     */
    colourArray[c] = (colourArray[c] - blackArray[c])/(greyDiff[c])*255;
    // Not enough pins to turn off the current LED colour, have to let the decoder switch to another colour
  } 
}

