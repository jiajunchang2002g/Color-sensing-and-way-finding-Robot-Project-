float closeness(float colour1[NO_COLOURS], float colour2[NO_COLOURS]) {
  float squaredSum = 0;
  for(int c = 0; c < NO_COLOURS; c++){  
      squaredSum += sq(colour1[c] - colour2[c]);
  }
  return sqrt(squaredSum);
}

#define NUM_TRAINING_DATA 45
int coloursX[NUM_TRAINING_DATA] = {
  WHITE_ENUM, WHITE_ENUM, WHITE_ENUM, WHITE_ENUM, WHITE_ENUM, // 5
  RED_ENUM, RED_ENUM, RED_ENUM, RED_ENUM, RED_ENUM, RED_ENUM, // 6
  ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM,  // 6
  ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, ORANGE_ENUM, // 4
  GREEN_ENUM, GREEN_ENUM, GREEN_ENUM, GREEN_ENUM, GREEN_ENUM, GREEN_ENUM, // 6
  PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM, PURPLE_ENUM, // 7
  LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, // 6
  LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM ,LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM, LIGHT_BLUE_ENUM,  // 5
};

float coloursY[NUM_TRAINING_DATA][NO_COLOURS] = {
  // White
  {283.33, 290.17, 261.46}, {283.33, 288.22, 258.23},  {283.33, 289.20, 259.84}, {283.33, 259.89, 253.39}, {283.33, 269.66, 255.00}, 
  // Red
  {283.33, 174.89, 112.97}, {283.33, 172.93, 111.36}, {283.33, 173.91, 114.59}, {255.00, 169.02, 119.43}, {226.67, 181.72, 125.89}, {255.00, 170.00, 119.43},
  // Orange
  {283.33, 223.74, 117.82}, {283.33, 223.74, 116.20}, {283.33, 221.78, 116.20}, {297.50, 221.78, 116.20}, {297.50, 214.94, 90.38}, {283.33, 222.76, 114.59},
  {240.83, 211.03, 116.20}, {255.00, 211.03, 119.43}, {240.83, 211.03, 116.20}, {240.83, 211.03, 116.20},
  // Green
  {113.33, 157.30, 103.29}, {99.17, 160.23, 106.52}, {99.17, 150.46, 103.29}, {85.00, 157.30, 106.52}, {14.17, 156.32, 96.84},  {14.17, 157.30, 104.91},
  // Purple
  {184.17, 147.53, 195.28}, {184.17, 147.53, 195.28}, {226.67, 176.84, 206.58}, {198.33, 160.23, 201.74}, {184.17, 159.25, 198.51}, {141.67, 173.91, 179.15},  {127.50, 161.21, 180.76}, 
  // Light Blue
  {70.83, 200.29, 245.32}, {42.50, 198.33, 243.70}, {56.67, 203.22, 246.93}, {56.67, 206.15, 242.09}, {85.00, 213.97, 227.56}, {70.83, 211.03, 225.95},  
  {70.83, 210.06, 229.18}, {141.67, 250.11, 246.93}, {141.67, 250.11, 246.93}, {127.50, 249.14, 246.93}
};

// modified knn algo - use all the neighbours since sample size is so small, improves accuracy

int knnColourEnum(float measuredColour[]){ 
  #if DEBUG_KNN_COLOUR_ENUM == TRUE
    Serial.println("DEBUG_KNN_COLOUR_ENUM: Start");
  #endif

  // Calculate distances between all the points in the dataset
  int count[NO_ENUMS];
  float distancesSum[NO_ENUMS];
  for (int i = 0; i < NO_ENUMS; i++) {
    count[i] = 0;
    distancesSum[i] = 0; 
  }

  #if DEBUG_KNN_COLOUR_ENUM == TRUE
    Serial.println("DEBUG_KNN_COLOUR_ENUM: Dist Calc");
  #endif

  // Consolidate Data points by Colour
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

  // Classification - Choose the colour with the smallest distance
  int closestColour = NULL_ENUM;
  for (int i = 0; i < NO_ENUMS; i++) {
    // Mode too unstable of a metric to be used (not enough training data)
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
