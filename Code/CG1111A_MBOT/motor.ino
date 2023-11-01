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
  int center_line = 12;
  int difference = center_line - ultrasonic();

  if (difference > 0 && ultrasonic() > 0.1) {
    rightMotor.run(right_motorSpeed / difference);
    delay(100);
    rightMotor.run(right_motorSpeed);

  }
  else if (ultrasonic() < 0 && ultrasonic() < 30) {
  leftMotor.run(left_motorSpeed / difference);
  delay(100);
  leftMotor.run(left_motorSpeed);
  }
}

void turnLeft() {
  rightMotor.run(0.5 * right_motorSpeed);
  leftMotor.run(0.5 * -left_motorSpeed);
  delay(TURNING_TIME_MS * 2.4);
  stopMotor();
  delay(200);
  }

void turnRight() {
  leftMotor.run(0.5 * left_motorSpeed);
  rightMotor.run(0.5 * -right_motorSpeed);
  delay(TURNING_TIME_MS * 2.2);
  stopMotor();
  delay(200);
}

void uTurn() {
  turnLeft();
  turnLeft();
  stopMotor();
  delay(200);
}

void doubleLeftTurn() {
  turnLeft();
  delay(200);
  moveForward();
  delay(750);
  stopMotor();
  delay(200);
  turnLeft();
  delay(200);
  stopMotor();
  delay(200);
}

void doubleRightTurn() {
  turnRight();
  delay(200);
  moveForward();
  delay(750);
  stopMotor();
  delay(200);
  turnRight();
  delay(200);
  stopMotor();
  delay(200);
}

void setup() {
  Serial.begin(9600);
  delay(3000);
}

void loop () {
  doubleRightTurn();
  delay(1000);
}
