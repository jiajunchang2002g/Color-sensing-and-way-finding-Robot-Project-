#define DECA A0
#define DECB A1
//int COLOUR_DEC_PIN[] = {0, 1, 2}; // R, G, B

void initDecoder() {
  pinMode(DECA, OUTPUT);
  pinMode(DECB, OUTPUT);
}

void setDecoder(long a) {
  digitalWrite(DECB, a / 2);
  digitalWrite(DECA, a % 2);
  #ifdef DEBUG_SERIAL
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

// Unit Tests ///////////////////////////////////////////////////
void testDecoder() {
  for (int i = 0; i < 4; i += 1) {
    #ifdef DEBUG_SERIAL
      Serial.print("Decoder ");
      Serial.println(i);
    #endif
    setDecoder(i);
    delay(1000);

  }
}

void testAnalog(){
    Serial.print(" A2=");
    Serial.print(analogRead(A2));
    Serial.print(" A3=");
    Serial.println(analogRead(A3));
}