/*double ultrasonic(){ // returns distance in cm
  pinMode(ULTRASONIC, OUTPUT);
  digitalWrite(ULTRASONIC, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC, LOW);

  pinMode(ULTRASONIC, INPUT);
  long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
  double distance = duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100;
  return distance;
}*/

//MeUltrasonicSensor ultraSensor(PORT_1); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */
/*
double ultrasonic(){ // returns distance in cm
  Serial.println(ultraSensor.distanceCm());
  return ultraSensor.distanceCm();
}
*/