#include "MeMCore.h"
#define TURNING_TIME_MS 330 // The time duration (ms) for turning
#define ULTRASONIC 12
#define TIMEOUT 1000000
#define SPEED_OF_SOUND 330

MeDCMotor leftMotor(M1); // assigning leftMotor to port M1
MeDCMotor rightMotor(M2); // assigning RightMotor to port M2
int left_motorSpeed = -255;
int right_motorSpeed = 240;
// Setting motor speed to an integer between 1 and 255
// The larger the number, the faster the speed

double ultrasonic(){ // returns distance in cm
  pinMode(ULTRASONIC, OUTPUT);
  digitalWrite(ULTRASONIC, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC, LOW);

  pinMode(ULTRASONIC, INPUT);
  long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
  double distance = duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100;
  Serial.println(distance);
  return distance;
}

void StopMotor() {
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
  delay(TURNING_TIME_MS);
  StopMotor();
  }

void turnRight() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(-right_motorSpeed);
  delay(TURNING_TIME_MS * 0.9);
  StopMotor();
}

void uTurn() {
  turnLeft();
  turnLeft();
  StopMotor();
}

void doubleLeftTurn() {
turnLeft();
moveForward();
delay(1500);
turnLeft();
StopMotor();
}

void doubleRightTurn() {
turnRight();
moveForward();
delay(1500);
turnRight();
StopMotor();
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

void setup() {
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  moveForward();

if (ultrasonic() < 4 && ultrasonic() > 1.5) {
nudgeRight();
}
else if (ultrasonic() > 5 && ultrasonic() < 30) {
  nudgeLeft();
}
}
