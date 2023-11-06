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
MeUltrasonicSensor ultraSensor(PORT_2); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

double ultrasonic(){ // returns distance in cm
  return ultraSensor.distanceCm();
}


void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}

void wallFollower() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(right_motorSpeed);
  int center_line = 10;
  int difference = center_line - ultrasonic();

  if (difference > 0 && ultrasonic() > 0.1) {
    rightMotor.run(right_motorSpeed * (1 / ((0.08 * difference) + 1)));
    delay(25);
    rightMotor.run(right_motorSpeed);

  }
  else if (difference < 0 && ultrasonic() < 20) {
  leftMotor.run(left_motorSpeed * (1 / ((-0.08 * difference) + 1)));
  delay(25);
  leftMotor.run(left_motorSpeed);
  } 
  else if (ultrasonic() > 15 && ir_sensing_distance() == true) {
    rightMotor.run(right_motorSpeed * 0.9);
    delay(100);
    rightMotor.run(right_motorSpeed);
  }
}

void turnLeft() {
  rightMotor.run(right_motorSpeed);
  leftMotor.run(-left_motorSpeed);
  delay(TURNING_TIME_MS * 1.2);
  }

void turnRight() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(-right_motorSpeed);
  delay(TURNING_TIME_MS * 1.1);
}

void uTurn() {
rightMotor.run(right_motorSpeed);
  leftMotor.run(-left_motorSpeed);
  delay(TURNING_TIME_MS * 2.1);
}

void doubleLeftTurn() {
 rightMotor.run(right_motorSpeed);
  leftMotor.run(-left_motorSpeed);
  delay(TURNING_TIME_MS * 1.2);
  wallFollower();
  delay(750);
  stopMotor();
  delay(50);
 rightMotor.run(right_motorSpeed);
  leftMotor.run(-left_motorSpeed);
  delay(TURNING_TIME_MS * 1.2);
  delay(50);
}

void doubleRightTurn() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(-right_motorSpeed);
  delay(TURNING_TIME_MS * 1.1);
  wallFollower();
  delay(750);
   leftMotor.run(left_motorSpeed);
  rightMotor.run(-right_motorSpeed);
  delay(TURNING_TIME_MS * 1.1);
  delay(50);
}


/*
void setup() {
  Serial.begin(9600);
  delay(3000);
}

void loop () {
  doubleRightTurn();
  delay(1000);
*/
