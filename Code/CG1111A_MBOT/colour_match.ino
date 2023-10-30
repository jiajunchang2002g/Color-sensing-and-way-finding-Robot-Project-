// Implementing KNN for colour detection - Don't need to hardcode ranges

float closeness(float colour1[NO_COLOURS], float colour2[NO_COLOURS]) {
  float squaredSum = 0;
  for(int c = 0; c < NO_COLOURS; c++){  
      squaredSum += sq(colour1[c] - colour2[c]);
  }
  return sqrt(squaredSum);
}

// Training Data
#define NUM_TRAINING_DATA 12
int coloursX[NUM_TRAINING_DATA] = {
  RED_ENUM, GREEN_ENUM, ORANGE_ENUM, 
  PURPLE_ENUM, LIGHT_BLUE_ENUM, WHITE_ENUM, 
  RED_ENUM, GREEN_ENUM, ORANGE_ENUM, 
  PURPLE_ENUM, LIGHT_BLUE_ENUM, WHITE_ENUM};

float coloursY[NUM_TRAINING_DATA][NO_COLOURS] = {
  {255, 0, 0},  {0, 255, 0},  {255, 128, 0},
  {255, 0, 255}, {0, 0, 255}, {255, 255, 255}, 
  {150.00, 12.82, 67.32}, {-30.00, 92.60, 81.60}, {165.00, 102.57, 77.52},
  {60.00, 65.53, 173.40}, {15.00, 170.95, 224.40}, {180.00, 246.45, 242.76}
};

// knn algo - use all the neighbours since sample size so small, check data/

int knnColourEnum(float measuredColour[]){ // Use all data for accuracy
  #if DEBUG_KNN_COLOUR_ENUM == TRUE
    Serial.println("DEBUG_KNN_COLOUR_ENUM: Start");
  #endif

  int count[NO_ENUMS];
  float distancesSum[NO_ENUMS];
  for (int i = 0; i < NO_ENUMS; i++) {
    count[i] = 0;
    distancesSum[i] = 0; 
  }

  #if DEBUG_KNN_COLOUR_ENUM == TRUE
    Serial.println("DEBUG_KNN_COLOUR_ENUM: Dist Calc");
  #endif

  for (int i = 0; i < NUM_TRAINING_DATA; i++) {
    float dist = closeness(measuredColour, coloursY[i]);
    distancesSum[coloursX[i]] += dist;
    count[coloursX[i]] += 1;
    #if DEBUG_KNN_COLOUR_ENUM == TRUE
      Serial.print("DEBUG_KNN_COLOUR_ENUM: i=");
      Serial.print(i);
      Serial.print(" coloursX[i]=");
      Serial.print(coloursX[i]);
      Serial.print(" dist=");
      Serial.print(dist);
      Serial.print(" distancesSum[coloursX[i]]=");
      Serial.println(distancesSum[coloursX[i]]);
    #endif
  }
  
  #if DEBUG_KNN_COLOUR_ENUM == TRUE
    Serial.println("DEBUG_KNN_COLOUR_ENUM: Classification");
  #endif
  // Classification
  int closestColour = NULL_ENUM;
  for (int i = 0; i < NO_ENUMS; i++) {
    if (closestColour == NULL_ENUM || 
        // count[i] > count[closestColour] || (count[i] == count[closestColour] && // Mode too unstable of a metric to be used (not enough training data)
        (count[i] !=0 && count[closestColour] != 0 && distancesSum[i]/count[i] < distancesSum[closestColour]/count[closestColour])
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

  //return getColourEnum(measuredColourForEnum);
  int colourEnum = knnColourEnum(measuredColourForEnum);

  #if DEBUG_COLOUR_ENUM == TRUE
    Serial.print("DEBUG_COLOUR_ENUM: ");
    serialPrintColour(colourEnum);
    Serial.println("");
  #endif

  return colourEnum;
}

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
