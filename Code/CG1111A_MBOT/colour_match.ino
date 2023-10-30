int getColourEnum(float measuredColour[]) {
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



// Implementing KNN for colour detection

float closeness(float colour1[NO_COLOURS], float colour2[NO_COLOURS]) {
  float squaredSum = 0;
  for(int c = 0; c < NO_COLOURS; c++){  
      squaredSum += sq(colour1[0] - colour2[0]);
  }
  return sqrt(squaredSum);
}


// Training Data
#define NUM_TRAINING_DATA 6
int coloursX[NUM_TRAINING_DATA] = {RED_ENUM, GREEN_ENUM, ORANGE_ENUM, PURPLE_ENUM, LIGHT_BLUE_ENUM, WHITE_ENUM};

float coloursY[NUM_TRAINING_DATA][NO_COLOURS] = {
  {255, 0, 0},
  {0, 255, 0},
  {255, 255, 255},
  {255, 255, 255},
  {0, 0, 255},
  {255, 255, 255}
};


// knn algo

int knnColourEnum(float measuredColour[]){ // Use all data for accuracy
  int count[NO_ENUMS];
  float distancesSum[NO_ENUMS];
  for (int i = 0; i < NO_ENUMS; i++) {
    count[i] = 0;
    distancesSum[i] = -1; 
  }

  for (int i = 0; i < NUM_TRAINING_DATA; i++) {
    float dist = closeness(measuredColour, coloursY[i]);
    distancesSum[coloursX[i]] += dist;
    count[coloursX[i]] += 1;
  }

  // Classification
  int closestColour = NULL_ENUM;
  for (int i = 0; i < NO_ENUMS; i++) {
    if (closestColour == NULL_ENUM || 
        // count[i] > count[closestColour] || (count[i] == count[closestColour] && // Mode too unstable of a metric to be used (not enough training data)
        distancesSum[i]/count[i] < distancesSum[closestColour]/count[closestColour] //)
    ){
      closestColour = i;
    }
  }
  return closestColour;
}


int getColourEnum(){
  float measuredColour[NO_COLOURS];
  readColour(NO_COLOURS, measuredColour);
  //return getColourEnum(measuredColour);
  return knnColourEnum(measuredColour);
}
