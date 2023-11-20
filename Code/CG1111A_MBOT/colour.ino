/*
 * Code here is on reading the RGB colour values using the LDR and LEDs.
 * 
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
     delay(LDR_WAIT);
  }
  return value / count;
}

/* Calibration --------------------------------------------------------------------------------------------- */

void setBalance(){
  Serial.println("Put White Sample For Calibration ...");
  delay(5000);           // delay for five seconds for getting sample ready

  // scan the white sample.
  // go through one colour at a time, set the maximum reading for each colour -- red, green and blue to the white array
  for(int c = 0; c < NO_COLOURS; c++){    
    setDecoder(COLOUR_DEC_PIN[c]); // Turn on LED
    delay(RGB_WAIT);
    whiteArray[c] = getAvgReading(5);  // scan 5 times and return the average,
  }

  // done scanning white, time for the black sample.
  // set black balance
  Serial.println("Put Black Sample For Calibration ...");
  delay(5000); // delay for five seconds for getting sample ready 

  // go through one colour at a time, set the minimum reading for red, green and blue to the black array
  for(int c = 0; c < NO_COLOURS; c++){    
    setDecoder(COLOUR_DEC_PIN[c]); // Turn on LED
    delay(RGB_WAIT);
    blackArray[c] = getAvgReading(5); // scan 5 times and return the average,
    // the differnce between the maximum and the minimum gives the range
    greyDiff[c] = whiteArray[c] - blackArray[c];
  }

  // delay another 5 seconds for getting ready colour objects
  Serial.println("Colour Sensor Is Ready.");
  delay(5000);
}

/* Reading value ----------------------------------------------------------------------------------------- */

void readColour(int noColours, float colourArray[]) {
  for(int c = 0; c < noColours; c++){       
    // turn ON the LED, red, green or blue, one colour at a time.
    setDecoder(COLOUR_DEC_PIN[c]);
    delay(RGB_WAIT);
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

