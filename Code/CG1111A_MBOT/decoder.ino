void initDecoder() {
  pinMode(DECA, OUTPUT);
  pinMode(DECB, OUTPUT);
}

void initLedButton() {
  led.setpin(13);
  pinMode(A7,INPUT); 
}

void startOnButtonPress(){
  while (analogRead(A7) > 10){}
}

void setDecoder(long a) {
  digitalWrite(DECB, a / 2);
  digitalWrite(DECA, a % 2);
  #if DEBUG_DECODER == TRUE
    Serial.print("DEBUG_DECODER: ");
    Serial.print(a / 2);
    Serial.print(' ');
    Serial.println(a % 2);
  #endif
}

void shineRed() { // Code for turning on the red LED only
  setDecoder(0);
}
void shineGreen() { // Code for turning on the green LED only
  setDecoder(1);
}
void shineBlue() { // Code for turning on the blue LED only
  setDecoder(2);
}

void shineIR() { // Code for turning on the IR emitter only
  setDecoder(3);
}

