// Returns if the action has ended
bool colourAction (int colour) {
  // Error Condition
  #if DEBUG_LOOP_LOGIC == TRUE
    Serial.print("Colour: ");
    Serial.print(colour);
    Serial.print("\n");
  #endif

  switch (colour) {
    case RED_ENUM:
      turnLeft();
      return false;
    case GREEN_ENUM:
      turnRight();
      return false;
    case ORANGE_ENUM:
      uTurn(); // 180° turn within the same grid
      return false;
    case PURPLE_ENUM:
      doubleLeftTurn(); // Two successive left-turns in two grids
      return false;
    case LIGHT_BLUE_ENUM:
      doubleRightTurn(); // Two successive right-turns in two grids
      return false;
    case WHITE_ENUM:
      celebrate();
      return true;
  }
  return false;
}

// https://education.makeblock.com/help/me-line-follower/
bool withinBlackLine(){
  int sensorState = lineFinder.readSensors();
  return sensorState == S1_IN_S2_IN; //true;
}

void mainLoopLogic() {
  bool ended = false;
  while (!ended) {
    wallFollower();
    // if within black line, stop motor, detect colour, and take corresponding action
    if (withinBlackLine()){
      #if DEBUG_LOOP_LOGIC == TRUE
        Serial.println("DEBUG_LOGIC: Saw Line");
      #endif
      stopMotor();
      int colour = getColourEnum();
      ended = colourAction(colour);
    }
  }
}
