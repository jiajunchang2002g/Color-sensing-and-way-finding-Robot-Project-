
// Returns if the action has ended
bool colourAction (int colour) {
  // Error Condition
  #ifdef DEBUG_SERIAL
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

void lineFollowing() {
  // Read ultrasonic sensing distance (choose an appropriate timeout)
  // Read IR sensing distance (turn off IR, read IR detector, turn on IR, read IR detector, estimate distance)
  // else if too near to left wall, nudge right
  // else if too near to right wall, nudge left
  // else move forward
}

bool withinBlackLine(){
  return true;
}

void mainLoopLogic() {
  bool ended = false;
  while (!ended) {
    lineFollowing();

    // if within black line, stop motor, detect colour, and take corresponding action
    if (withinBlackLine()){
      stopMotor();
      int colour = getColourEnum();
      ended = colourAction(colour);
    }
  }
}
