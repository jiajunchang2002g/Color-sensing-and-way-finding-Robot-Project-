#include <MeMCore.h>

/*
void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

*/

int LED_A0 = A0;
int LED_A1 = A1;
int LED_A2 = A2;
int LED_A3 = A3;

void setup() {
 // Any setup code here runs only once:
  pinMode(LED_A0, OUTPUT);
  pinMode(LED_A1, OUTPUT);
  Serial.begin(9600);
}
void loop() {
 // The main code here will run repeatedly (i.e., looping):
 //celebrate(); // play the tune specified in the function celebrate()
 digitalWrite(A0, 1);
 digitalWrite(A1, 1);
 delay(1000);

  digitalWrite(LED_A1, LOW);
  digitalWrite(LED_A0, HIGH);
  delay(1000);
  digitalWrite(LED_A0, LOW);
  digitalWrite(LED_A1, HIGH);
  delay(1000);
}