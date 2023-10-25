/* ColourSensor.txt
 * Designed by Dr Henry Tan
 * For CG1111A Photoelectric Sensors Studio
 */

// OTHER: TODO - CLEANUP
int COLOUR_DEC_PIN[] = {0, 1, 2}; // R, G, B


// Colours
// Pins
#define LDR A3   //LDR sensor pin at A0
#define LED 13  //Check Indicator to signal Calibration Completed

// Define time delay before the next RGB colour turns ON to allow LDR to stabilize
#define RGBWait 200 //in milliseconds 
// Define time delay before taking another LDR reading
#define LDRWait 10 //in milliseconds 


// Define colour sensor LED pins
int ledArray[] = {2,3,4};

//placeholders for colour detected
int red = 0;
int green = 0;
int blue = 0;

//Calibration Metrics
float whiteArray[] = {956, 804, 905}; // {0,0,0};
float blackArray[] = {943, 758, 756}; // {0,0,0};
float greyDiff[] = {13,86,149}; // {0,0,0};

void colour_setup(){
  pinMode(LED,OUTPUT);   //Check Indicator -- OFF during Calibration
  //begin serial communication
  setBalance();  //calibration
  digitalWrite(LED, HIGH); //Check Indicator -- ON after Calibration
}


int getAvgReading(int times){      
  //find the average reading for the requested number of times of scanning LDR
  int reading;
  int total = 0;
  //take the reading as many times as requested and add them up
  for(int i = 0;i < times;i++){
     reading = analogRead(LDR);
     total = reading + total;
     delay(LDRWait);
  }
  //calculate the average and return it
  return total/times;
}

// Calibration ////////////////////////////////////////////////////////////////////////////////////

void setBalance(){
  //set white balance
  Serial.println("Put White Sample For Calibration ...");
  delay(5000);           //delay for five seconds for getting sample ready
  digitalWrite(LED,LOW); //Check Indicator OFF during Calibration
  //scan the white sample.
  //go through one colour at a time, set the maximum reading for each colour -- red, green and blue to the white array
  for(int i = 0;i<=2;i++){
    setDecoder(COLOUR_DEC_PIN[i]); // Turn on LED
    delay(RGBWait);
    whiteArray[i] = getAvgReading(5);         //scan 5 times and return the average,
  }
  //done scanning white, time for the black sample.
  //set black balance
  Serial.println("Put Black Sample For Calibration ...");
  delay(5000);     //delay for five seconds for getting sample ready 

  //go through one colour at a time, set the minimum reading for red, green and blue to the black array
  for(int i = 0;i<=2;i++){
    setDecoder(COLOUR_DEC_PIN[i]); // Turn on LED
    delay(RGBWait);
    blackArray[i] = getAvgReading(5);         //scan 5 times and return the average,
    //the differnce between the maximum and the minimum gives the range
    greyDiff[i] = whiteArray[i] - blackArray[i];
  }

  //delay another 5 seconds for getting ready colour objects
  Serial.println("Colour Sensor Is Ready.");
  delay(5000);
}

// Reading Value ////////////////////////////////////////////////////////////////////////////////////////

void read_colour(int noColours, float colourArray[]) {
  for(int c = 0; c <= noColours; c++){       
    //turn ON the LED, red, green or blue, one colour at a time.
    setDecoder(COLOUR_DEC_PIN[c]);
    delay(RGBWait);
    colourArray[c] = getAvgReading(5);

    /* 
     * the average reading returned minus the lowest value divided by the maximum possible range, 
     * multiplied by 255 will give a value between 0-255, 
     * representing the value for the current reflectivity (i.e. the colour LDR is exposed to)
     */
    colourArray[c] = (colourArray[c] - blackArray[c])/(greyDiff[c])*255;
    //Not enough pins to turn off the current LED colour
  } 
}


// Unit Tests /////////////////////////////////////////////////////////////////////////////

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
  int noColours = 3;
  #ifdef DEBUG_SERIAL
    testPrint(noColours, "whiteArray", whiteArray);
    testPrint(noColours, "blackArray", blackArray);
    testPrint(noColours, "greyDiff", greyDiff);
  #endif
}

void testColourReading() {
  int noColours = 3;
  float colourArray[] = {0,0,0};
  read_colour(noColours, colourArray);
  for(int c = 0; c < noColours; c++){  
    #ifdef DEBUG_SERIAL
      Serial.print(colourStr[c]);
      Serial.println(int(colourArray[c])); //show the value for the current colour LED, which corresponds to either the R, G or B of the RGB code
    #endif
  }

}
