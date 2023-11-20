/**
 * Code here is on classifying RGB data into colours. This is done through a modified KNN algorithm.
 */

#include "colour_training_data.h"

/* Distance Function --------------------------------------------------------------------- */
float closeness(float colour1[NO_COLOURS], float colour2[NO_COLOURS]) {
  float squaredSum = 0;
  for(int c = 0; c < NO_COLOURS; c++){  
      squaredSum += sq(colour1[c] - colour2[c]);
  }
  return sqrt(squaredSum);
}

/* Modified KNN Algorithm ----------------------------------------------------------------- */
/**
 * Uses all the neighbours since sample size is so small, improves accuracy
 * Average Distance is used as a metric instead of mode
 */
int knnColourEnum(float measuredColour[]){ 
  #if DEBUG_KNN_COLOUR_ENUM == TRUE
    Serial.println("DEBUG_KNN_COLOUR_ENUM: Start");
  #endif

  /* Calculate distances between all the points in the dataset  -----------------------*/
  int count[NO_ENUMS];
  float distancesSum[NO_ENUMS];
  for (int i = 0; i < NO_ENUMS; i++) {
    count[i] = 0;
    distancesSum[i] = 0; 
  }
  #if DEBUG_KNN_COLOUR_ENUM == TRUE
    Serial.println("DEBUG_KNN_COLOUR_ENUM: Dist Calc");
  #endif

  /* Consolidate Data points by Colour  -----------------------------------------------*/
  for (int i = 0; i < NUM_TRAINING_DATA; i++) {
    float dist = closeness(measuredColour, coloursX[i]);
    distancesSum[coloursY[i]] += dist;
    count[coloursY[i]] += 1;
    #if DEBUG_KNN_COLOUR_ENUM == TRUE
      Serial.print("DEBUG_KNN_COLOUR_ENUM: i=");
      Serial.print(i);
      Serial.print(" coloursY[i]=");
      Serial.print(coloursY[i]);
      Serial.print(" dist=");
      Serial.print(dist);
      Serial.print(" distancesSum[coloursY[i]]=");
      Serial.println(distancesSum[coloursY[i]]);
    #endif
  }
  #if DEBUG_KNN_COLOUR_ENUM == TRUE
    Serial.println("DEBUG_KNN_COLOUR_ENUM: Classification");
  #endif

  /* Classification - Choose the colour with the smallest distance ------------------*/
  int closestColour = NULL_ENUM;
  for (int i = 0; i < NO_ENUMS; i++) {
    if (closestColour == NULL_ENUM || 
        (count[i] != 0 && count[closestColour] != 0 && 
        distancesSum[i] / count[i] < distancesSum[closestColour] / count[closestColour])
    ){
      closestColour = i;
    }
  }
  #if DEBUG_KNN_COLOUR_ENUM == TRUE
    Serial.print("DEBUG_KNN_COLOUR_ENUM: Output - closestColour =");
   Serial.println(closestColour);
  #endif

  return closestColour;
  return NULL_ENUM;
}

/* Combined Colour Detection Function ------------------------------------------------------------- */

float measuredColourForEnum[NO_COLOURS];
int getColourEnum(){
  #if DEBUG_COLOUR_ENUM == TRUE
    Serial.println("DEBUG_COLOUR_ENUM: Reading Colours");
  #endif

  readColour(NO_COLOURS, measuredColourForEnum);
  
  #if DEBUG_COLOUR_ENUM == TRUE
    Serial.print("DEBUG_COLOUR_ENUM: RGB Values {");
    Serial.print(measuredColourForEnum[0]);
    Serial.print(", ");
    Serial.print(measuredColourForEnum[1]);
    Serial.print(", ");
    Serial.print(measuredColourForEnum[2]);
    Serial.println("} ");
  #endif

  int colourEnum = knnColourEnum(measuredColourForEnum);

  #if DEBUG_COLOUR_ENUM == TRUE
    Serial.print("DEBUG_COLOUR_ENUM: ");
    serialPrintColour(colourEnum);
    Serial.println("");
  #endif

  ledShowColour(colourEnum);
  return colourEnum;
}

/* Debugging Functionality ----------------------------------------------------------------- */

#if DEBUG_COLOUR_ENUM == TRUE
  void serialPrintColour(int colourEnum) {
    Serial.print("( ");
    switch(colourEnum) {
      case RED_ENUM:
        Serial.print("Red");
        break;
      case GREEN_ENUM:
        Serial.print("Green");
        break;
      case ORANGE_ENUM:
        Serial.print("Orange");
        break;
      case PURPLE_ENUM:
        Serial.print("Purple");
        break;
      case LIGHT_BLUE_ENUM:
        Serial.print("Light Blue");
        break;
      case WHITE_ENUM:
        Serial.print("White");
        break;
    }  

    Serial.print(" ");
    Serial.print(colourEnum);
    Serial.print(" )");
  }
#endif

void ledShowColour(int colour) {
  switch (colour) {
    case RED_ENUM:
      led.setColor(255, 0, 0); 
      led.show();
      break;
    case GREEN_ENUM:
      led.setColor(0, 255, 0); 
      led.show();
      break;
    case ORANGE_ENUM:
      led.setColor(255, 128, 0); 
      led.show();
      break;
    case PURPLE_ENUM:
      led.setColor(255, 0, 255); 
      led.show();
      break;
    case LIGHT_BLUE_ENUM:
      led.setColor(0, 0, 255); 
      led.show();
      break;
    case WHITE_ENUM:
      led.setColor(255, 255, 255); 
      led.show();
      break;
  }
}
