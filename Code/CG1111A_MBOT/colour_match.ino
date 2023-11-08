// Implementing KNN for colour detection - Don't need to hardcode ranges

float closeness(float colour1[NO_COLOURS], float colour2[NO_COLOURS]) {
  float squaredSum = 0;
  for(int c = 0; c < NO_COLOURS; c++){  
      squaredSum += sq(colour1[c] - colour2[c]);
  }
  return sqrt(squaredSum);
}

// Training Data
#define NUM_TRAINING_DATA 43
int coloursX[NUM_TRAINING_DATA] = {
  WHITE_ENUM, WHITE_ENUM, WHITE_ENUM, WHITE_ENUM, WHITE_ENUM, // 5
  RED_ENUM, RED_ENUM, RED_ENUM, RED_ENUM, RED_ENUM, // 5
  ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, // 7
  GREEN_ENUM, GREEN_ENUM, GREEN_ENUM, GREEN_ENUM, GREEN_ENUM, GREEN_ENUM, // 6
  PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM,  // 5 
  PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM,  // 5 
  LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, // 5
  LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM // 5
  //, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM // 8
};

float coloursY[NUM_TRAINING_DATA][NO_COLOURS] = {
  {269.17, 258.91, 256.61}, {198.33, 255.00, 250.16}, {212.50, 260.86, 251.77}, {283.33, 259.89, 253.39}, {283.33, 269.66, 255.00}, 
  {269.17, 88.91, 87.15}, {255.00, 87.93, 82.31}, {255.00, 86.95, 80.70}, {198.33, 97.70, 93.61}, {283.33, 85.98, 82.31}, 
  {226.67, 160.23, 91.99}, {240.83, 157.30, 83.92}, {226.67, 155.34, 90.38}, {198.33, 99.66, 93.61}, {269.17, 147.53, 82.31},{269.17, 153.39, 91.99}, {283.33, 162.18, 96.84}, 
  {113.33, 157.30, 103.29}, {99.17, 160.23, 106.52}, {99.17, 150.46, 103.29}, {85.00, 157.30, 106.52}, {14.17, 156.32, 96.84},  {14.17, 157.30, 104.91},
  {184.17, 147.53, 195.28}, {184.17, 147.53, 195.28}, {226.67, 176.84, 206.58}, {198.33, 160.23, 201.74}, {184.17, 159.25, 198.51}, // Too high values
  {127.50, 150.46, 204.97}, {113.33, 144.60, 201.74}, {141.67, 173.91, 179.15}, {113.33, 166.09, 180.76}, {127.50, 161.21, 180.76}, 
  {70.83, 200.29, 245.32}, {42.50, 198.33, 243.70}, {56.67, 203.22, 246.93}, {56.67, 206.15, 242.09}, {85.00, 213.97, 227.56}, 
  {113.33, 201.26, 240.47}, {70.83, 211.03, 225.95}, {113.33, 168.05, 114.59}, {113.33, 168.05, 116.20}, {70.83, 210.06, 229.18}
  //{141.67, 200.29, 238.86}, {141.67, 196.38, 237.25}, {127.50, 201.26, 238.86}, {127.50, 203.22, 238.86}, {141.67, 205.17, 238.86}, {113.33, 168.05, 114.59},{113.33, 168.05, 116.20},  
};

// modified knn algo - use all the neighbours since sample size so small, check data/

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

  ledShowColour(colourEnum);
  return colourEnum;
}

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
