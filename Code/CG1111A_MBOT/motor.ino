#include "MeMCore.h"
#define TURNING_TIME_MS 330 // The time duration (ms) for turning
#define ULTRASONIC 12
#define TIMEOUT 1000000
#define SPEED_OF_SOUND 330

int left_motorSpeed = -255;
int right_motorSpeed = 240;
// Setting motor speed to an integer between 1 and 255
// The larger the number, the faster the speed


void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}

void moveForward() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(right_motorSpeed);
}

void turnLeft() {
  rightMotor.run(right_motorSpeed);
  leftMotor.run(-left_motorSpeed);
  delay(TURNING_TIME_MS * 1.2);
  stopMotor();
  }

void turnRight() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(-right_motorSpeed);
  delay(TURNING_TIME_MS * 0.9);
  stopMotor();
}

void uTurn() {
  turnLeft();
  turnLeft();
  stopMotor();
}

void doubleLeftTurn() {
  turnLeft();
  moveForward();
  delay(1500);
  turnLeft();
  stopMotor();
}

void doubleRightTurn() {
  turnRight();
  moveForward();
  delay(1500);
  turnRight();
  stopMotor();
}

void nudgeLeft() {
  leftMotor.run(left_motorSpeed * 0.7);
  delay(10);
  leftMotor.run(left_motorSpeed);
}

void nudgeRight() {
  rightMotor.run(right_motorSpeed * 0.85);
  delay(10);
  rightMotor.run(right_motorSpeed);
}

/*
void setup() {
  Serial.begin(9600);
  delay(3000);
}
*/

void wallFollower() {
  moveForward();
  if (ultrasonic() < 4 && ultrasonic() > 1.5) {
  nudgeRight();
  }
  else if (ultrasonic() > 5 && ultrasonic() < 30) {
    nudgeLeft();
  }
}
