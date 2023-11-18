bool colourAction (int colour) {
  /* #if DEBUG_LOOP_LOGIC == TRUE
    Serial.print("Colour: ");
    Serial.print(colour);
    Serial.print("\n");
    #endif
  */
  switch (colour) {
    case RED_ENUM:
      turnLeft();
      return false;
    case GREEN_ENUM:
      turnRight();
      return false;
    case ORANGE_ENUM:
      uTurn(); 
      return false;
    case PURPLE_ENUM:
      doubleLeftTurn(); 
      return false;
    case LIGHT_BLUE_ENUM:
      doubleRightTurn(); 
      return false;
    case WHITE_ENUM:
      celebrate();
      return true;
  }
  return false;
}

bool withinBlackLine(){
  int sensorState = lineFinder.readSensors();
  return sensorState == S1_IN_S2_IN; //true;
}

void mainLoopLogic() {
  bool ended = false;
  while (!ended) {
    wallFollower();
    if (withinBlackLine()){
      // #if DEBUG_LOOP_LOGIC == TRUE
      //  Serial.println("DEBUG_LOGIC: Saw Line");
      // #endif
      stopMotor();
      int colour = getColourEnum();
      ended = colourAction(colour);
    }
  }
}
