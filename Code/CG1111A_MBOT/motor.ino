#define TURNING_TIME_MS 330 
#define ULTRASONIC 12
#define TIMEOUT 2000
#define SPEED_OF_SOUND 330
#define PID_SENSITIVITY 0.1
#define LEFT_MOTOR_SPEED -255
#define RIGHT_MOTOR_SPEED 255

void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}

void wallFollower() {
  leftMotor.run(LEFT_MOTOR_SPEED);
  rightMotor.run(RIGHT_MOTOR_SPEED);
  double centerLine = 8.8;
  double difference = centerLine - ultrasonic();

  if (difference > 0 && ultrasonic() > 0.1) {
    rightMotor.run(RIGHT_MOTOR_SPEED * (1 / ((PID_SENSITIVITY * difference) + 1)));
    delay(25);
    rightMotor.run(RIGHT_MOTOR_SPEED);

  }
  else if (difference < 0 && ultrasonic() < 20) {
    leftMotor.run(LEFT_MOTOR_SPEED * (1 / ((-PID_SENSITIVITY * difference) + 1)));
    delay(25);
    leftMotor.run(LEFT_MOTOR_SPEED);
  } 
  else if (ultrasonic() > 15 && isNearIR() == true) {
    led.setColor(255, 192, 203); 
    led.show();
    rightMotor.run(RIGHT_MOTOR_SPEED * 0.9);
    delay(100);
    rightMotor.run(RIGHT_MOTOR_SPEED);
  }
}

void turnLeft() {
  rightMotor.run(RIGHT_MOTOR_SPEED);
  leftMotor.run(-LEFT_MOTOR_SPEED);
  delay(TURNING_TIME_MS * 1.0);
}

void turnRight() {
  leftMotor.run(LEFT_MOTOR_SPEED);
  rightMotor.run(-RIGHT_MOTOR_SPEED);
  delay(TURNING_TIME_MS * 0.95);
}

void uTurn() {
  if (ultrasonic() > 6) {
    rightMotor.run(RIGHT_MOTOR_SPEED);
    leftMotor.run(-LEFT_MOTOR_SPEED);
    delay(TURNING_TIME_MS * 1.85); 
  }
  else {
    rightMotor.run(-RIGHT_MOTOR_SPEED);
    leftMotor.run(LEFT_MOTOR_SPEED);
    delay(TURNING_TIME_MS * 1.85);
  }
}

void doubleLeftTurn() {
  rightMotor.run(RIGHT_MOTOR_SPEED);
  leftMotor.run(-LEFT_MOTOR_SPEED);
  delay(TURNING_TIME_MS * 1.1); 
  rightMotor.run(RIGHT_MOTOR_SPEED);
  leftMotor.run(0.93 * LEFT_MOTOR_SPEED);
  delay(900); 
  stopMotor();
  delay(50);
  rightMotor.run(RIGHT_MOTOR_SPEED);
  leftMotor.run(-LEFT_MOTOR_SPEED);
  delay(TURNING_TIME_MS * 1.0);
  delay(50);
  rightMotor.run(RIGHT_MOTOR_SPEED);
  leftMotor.run(LEFT_MOTOR_SPEED);
  delay(300);
}

void doubleRightTurn() {
  leftMotor.run(LEFT_MOTOR_SPEED);
  rightMotor.run(-RIGHT_MOTOR_SPEED);
  delay(TURNING_TIME_MS * 0.9); 
  wallFollower();
  delay(700);
  leftMotor.run(LEFT_MOTOR_SPEED);
  rightMotor.run(-RIGHT_MOTOR_SPEED);
  delay(TURNING_TIME_MS * 0.9);
  delay(50);
}
