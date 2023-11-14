#define TURNING_TIME_MS 330 // The time duration (ms) for turning
#define ULTRASONIC 12
#define TIMEOUT 2000
#define SPEED_OF_SOUND 330
#define PID_SENSITIVITY 0.1

int left_motorSpeed = -255;
int right_motorSpeed = 255;
// Setting motor speed to an integer between 1 and 255
// The larger the number, the faster the speed

void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}

void wallFollower() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(right_motorSpeed);
  double center_line = 8.8;
  double difference = center_line - ultrasonic();

  if (difference > 0 && ultrasonic() > 0.1) {
    rightMotor.run(right_motorSpeed * (1 / ((PID_SENSITIVITY * difference) + 1)));
    delay(25);
    rightMotor.run(right_motorSpeed);

  }
  else if (difference < 0 && ultrasonic() < 20) {
    leftMotor.run(left_motorSpeed * (1 / ((-PID_SENSITIVITY * difference) + 1)));
    delay(25);
    leftMotor.run(left_motorSpeed);
  } 
  else if (ultrasonic() > 15 && ir_sensing_distance() == true) {
    led.setColor(255, 192, 203); 
    led.show();
    rightMotor.run(right_motorSpeed * 0.9);
    delay(100);
    rightMotor.run(right_motorSpeed);
  }
}

void turnLeft() {
  rightMotor.run(right_motorSpeed);
  leftMotor.run(-left_motorSpeed);
  delay(TURNING_TIME_MS * 1.0);
  }

void turnRight() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(-right_motorSpeed);
  delay(TURNING_TIME_MS * 1.0);
}

void uTurn() {
if (ultrasonic() > 6) {
  rightMotor.run(right_motorSpeed);
  leftMotor.run(-left_motorSpeed);
  delay(TURNING_TIME_MS * 1.85); // from 2.1
}
  else {
  rightMotor.run(-right_motorSpeed);
  leftMotor.run(left_motorSpeed);
  delay(TURNING_TIME_MS * 1.85);
  }
}

void doubleLeftTurn() {
 rightMotor.run(right_motorSpeed);
  leftMotor.run(-left_motorSpeed);
  delay(TURNING_TIME_MS * 1.1); // Was 1.1
  wallFollower();
  delay(800); 
  stopMotor();
  delay(50);
 rightMotor.run(right_motorSpeed);
  leftMotor.run(-left_motorSpeed);
  delay(TURNING_TIME_MS * 1.0);
  delay(50);
}

void doubleRightTurn() {
  leftMotor.run(left_motorSpeed);
  rightMotor.run(-right_motorSpeed);
  delay(TURNING_TIME_MS * 0.9); // Was 1.1
  wallFollower();
  delay(700); //was 750, just tweaking a bit
   leftMotor.run(left_motorSpeed);
  rightMotor.run(-right_motorSpeed);
  delay(TURNING_TIME_MS * 0.9);
  delay(50);
}
