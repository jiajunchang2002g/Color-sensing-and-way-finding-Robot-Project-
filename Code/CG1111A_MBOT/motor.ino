#include "MeMCore.h"
#define TURNING_TIME_MS 330 // The time duration (ms) for turning
#define ULTRASONIC 12
#define TIMEOUT 2000
#define SPEED_OF_SOUND 330
MeDCMotor leftMotor(M1);
MeDCMotor rightMotor(M2);

int left_motorSpeed = -255;
int right_motorSpeed = 255;
// Setting motor speed to an integer between 1 and 255
// The larger the number, the faster the speed
MeUltrasonicSensor ultraSensor(PORT_1); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

double ultrasonic(){ // returns distance in cm
Serial.println(ultraSensor.distanceCm());
  return ultraSensor.distanceCm();
}


void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}

void moveForward() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(right_motorSpeed);
  int center_line = 10;
  int difference = center_line - ultrasonic();

  if (difference > 0 && ultrasonic() > 0.1) {
    rightMotor.run(right_motorSpeed * 0.7);
    delay(50 * difference);
    rightMotor.run(right_motorSpeed);

  }
  else if (ultrasonic() < 0 && ultrasonic() < 30) {
  leftMotor.run(left_motorSpeed * 0.7);
  delay(50 * difference);
  leftMotor.run(left_motorSpeed);
  }
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

void setup() {
  Serial.begin(9600);
  delay(3000);
}

void loop () {
  moveForward();
}

void loop () {
  moveForward();
}
