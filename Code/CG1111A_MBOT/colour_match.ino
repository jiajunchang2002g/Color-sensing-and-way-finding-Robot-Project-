#define NO_ENUMS 5
#define NO_COLOURS 3
#define RED_ENUM 0
#define GREEN_ENUM 1
#define ORANGE_ENUM 2
#define PURPLE_ENUM 3
#define LIGHT_BLUE_ENUM 4
#define NULL_ENUM -1

int coloursEnum[NO_ENUMS] = {RED_ENUM, GREEN_ENUM, ORANGE_ENUM, PURPLE_ENUM, LIGHT_BLUE_ENUM}; 

int colours[NO_ENUMS][NO_COLOURS] = {
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255},
  {255, 255, 255}
};

int coloursUpperRange[NO_ENUMS][NO_COLOURS] = {
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10}
};

int coloursLowerRange[NO_ENUMS][NO_COLOURS] = {
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10},
  {10, 10, 10}
};

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