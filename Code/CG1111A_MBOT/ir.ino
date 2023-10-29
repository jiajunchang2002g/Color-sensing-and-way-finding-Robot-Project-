#define IRDetector /* pin num */
int IREmitter = ;

void setup() {
  pinMode(IREmitter, OUTPUT);
  pinMode(IRDetector, INPUT);
}

void shineIR() {
  digitalWrite(IREmitter, HIGH);
}

double read_ir_distance() {
  digitalWrite(IREmitter, LOW); // get a reference reading for the ambient IR level
  delay(1000); // might need to adjust
  double reference_reading = analogRead(IRDetector);
  digitalWrite(IREmitter, HIGH); // turn on emitter to read the IR detector again to obtain the signal reading including both the emitted and ambient IR.
  delay(1000); 
  double signal_reading = analogRead(IRDetector);
  double intensity_diff = reference_reading - signal_reading;
  double distance = 

  return distance;
}
  
  
