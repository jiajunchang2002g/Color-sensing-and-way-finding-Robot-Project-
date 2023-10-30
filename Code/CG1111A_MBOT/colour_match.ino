/*int getColourEnum(float measuredColour[]) {
    for(int e = 0; e < NO_ENUMS; e++){  
    bool isColour = true;
    
    for(int c = 0; c < NO_COLOURS; c++){  
      int lowerBound = colours[e][c] - coloursLowerRange[e][c];
      int upperBound = colours[e][c] - coloursUpperRange[e][c];
      if (measuredColour[c] < lowerBound || measuredColour[c] > upperBound) {
        isColour = false;
      }
    }

    if (isColour) {
      return e;
    }
  }
  return NULL_ENUM;
}

*/

////////////////////////////////////////////////////////////////////////////////


// Implementing KNN for colour detection

float closeness(float colour1[NO_COLOURS], float colour2[NO_COLOURS]) {
  float squaredSum = 0;
  for(int c = 0; c < NO_COLOURS; c++){  
      squaredSum += sq(colour1[c] - colour2[c]);
  }
  return sqrt(squaredSum);
}


// Training Data
#define NUM_TRAINING_DATA 6
int coloursX[NUM_TRAINING_DATA] = {RED_ENUM, GREEN_ENUM, ORANGE_ENUM, PURPLE_ENUM, LIGHT_BLUE_ENUM, WHITE_ENUM};

float coloursY[NUM_TRAINING_DATA][NO_COLOURS] = {
  {255, 0, 0},
  {0, 255, 0},
  {255, 128, 0},
  {255, 0, 255},
  {0, 0, 255},
  {255, 255, 255}, 
};


// knn algo

int knnColourEnum(float measuredColour[]){ // Use all data for accuracy
  Serial.println("DEBUG_KNN_COLOUR_ENUM: Start");
  int count[NO_ENUMS];
  float distancesSum[NO_ENUMS];
  for (int i = 0; i < NO_ENUMS; i++) {
    count[i] = 0;
    distancesSum[i] = 0; 
  }

  Serial.println("DEBUG_KNN_COLOUR_ENUM: Dist Calc");
  for (int i = 0; i < NUM_TRAINING_DATA; i++) {
    float dist = closeness(measuredColour, coloursY[i]);
    distancesSum[coloursX[i]] += dist;
    count[coloursX[i]] += 1;

    Serial.print("DEBUG_KNN_COLOUR_ENUM: i=");
    Serial.print(i);
    Serial.print(" coloursX[i]=");
    Serial.print(coloursX[i]);
    Serial.print(" dist=");
    Serial.println(dist);
    Serial.println(" distancesSum[coloursX[i]]=");
    //Serial.println(distancesSum[coloursX[i]]);

  }
  
  Serial.print("DEBUG_KNN_COLOUR_ENUM: Classification");
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

  Serial.print("DEBUG_KNN_COLOUR_ENUM: closestColour =");
  Serial.println(closestColour);

  return closestColour;
  return NULL_ENUM;
}


float measuredColourForEnum[NO_COLOURS];
int getColourEnum(){
  Serial.println("get colour Enum");
  readColour(NO_COLOURS, measuredColourForEnum);
  
  Serial.print("DEBUG_COLOUR_ENUM: RGB Values ");
  Serial.print(measuredColourForEnum[0]);
  Serial.print(" ");
  Serial.print(measuredColourForEnum[1]);
  Serial.print(" ");
  Serial.println(measuredColourForEnum[2]);
  
  //return getColourEnum(measuredColourForEnum);
  int colourEnum = knnColourEnum(measuredColourForEnum);

  Serial.print("DEBUG_COLOUR_ENUM: ");
  Serial.println(colourEnum);
  
  return colourEnum;
  //return NULL_ENUM;
}
