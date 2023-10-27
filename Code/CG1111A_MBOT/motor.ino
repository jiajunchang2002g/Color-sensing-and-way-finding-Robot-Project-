#define TURNING_TIME_MS 330 // The time duration (ms) for turning
uint8_t motorSpeed = 255;
// Setting motor speed to an integer between 1 and 255
// The larger the number, the faster the speed


void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}


void moveForward() {
  leftMotor.run(motorSpeed);
  rightMotor.run(motorSpeed);
}


void turnLeft() {
  rightMotor.run(motorSpeed);
  leftMotor.run(-motorSpeed);
  delay(TURNING_TIME_MS);
  leftMotor.stop();
  rightMotor.stop();
  }


void turnRight() {
  leftMotor.run(motorSpeed);
  rightMotor.run(-motorSpeed);
  delay(TURNING_TIME_MS);
  rightMotor.stop();
  leftMotor.stop();
}


void uTurn() {
  rightMotor.run(motorSpeed);
  leftMotor.run(-motorSpeed);
  delay(2 * TURNING_TIME_MS);
  leftMotor.stop();
  rightMotor.stop();
}


void doubleLeftTurn() {
  rightMotor.run(motorSpeed);
  leftMotor.run(-motorSpeed);
  delay(TURNING_TIME_MS);
  leftMotor.run(motorSpeed);
  delay(TURNING_TIME_MS); //need to adjust this
  leftMotor.run(-motorSpeed);
  delay(TURNING_TIME_MS);
  leftMotor.stop();
  rightMotor.stop();
}


void doubleRightTurn() {
  rightMotor.run(-motorSpeed);
  leftMotor.run(motorSpeed);
  delay(TURNING_TIME_MS);
  rightMotor.run(motorSpeed);
  delay(TURNING_TIME_MS); //need to adjust this
  rightMotor.run(-motorSpeed);
  delay(TURNING_TIME_MS);
  leftMotor.stop();
  rightMotor.stop();
}


void nudgeLeft() {
  // leftMotor((motorSpeed * 0.8);  // Buggy
  delay(10);
  // leftMotor(motorSpeed); // Buggy
}


void nudgeRight() {
  // rightMotor(motorSpeed * 0.8); // Buggy
  delay(10);
  // rightMotor(motorSpeed);  // Buggy
}
