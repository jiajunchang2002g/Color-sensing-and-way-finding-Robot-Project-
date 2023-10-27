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

int getColourEnum(){
  float measuredColour[NO_COLOURS];
  readColour(NO_COLOURS, measuredColour);
  return getColourEnum(measuredColour);
}