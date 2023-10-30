#define IRDetector A2

 void setup() {
  pinMode(IRDetector, INPUT);
  Serial.begin(9600);
} 

void shineIR() {
  setDecoder(3);
}

double read_ir_distance() {
  double adc_distance = analogRead(IRDetector); //actually the value of detector's voltages
  return adc_distance;
}
  
if (distance < 635) {
  nudgeRight();
} else {
  nudgeLeft();
}


//the further the distance, the lower the voltage
//5V --> 1023
//3.1V --> 634.26
