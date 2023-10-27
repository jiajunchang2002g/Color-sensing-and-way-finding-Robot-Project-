void initDecoder() {
  pinMode(DECA, OUTPUT);
  pinMode(DECB, OUTPUT);
}

void setDecoder(long a) {
  digitalWrite(DECB, a / 2);
  digitalWrite(DECA, a % 2);
  #ifdef DEBUG_DECODER
    Serial.print(a / 2);
    Serial.print(' ');
    Serial.print(a % 2);
    Serial.print('\n');
  #endif
}

void shineRed() {// Code for turning on the red LED only
  setDecoder(0);
}
void shineGreen() {// Code for turning on the green LED only
  setDecoder(1);
}
void shineBlue() {// Code for turning on the blue LED only
  setDecoder(2);
}

void shineIR() {// Code for turning on the IR emitter only
  setDecoder(3);
}

