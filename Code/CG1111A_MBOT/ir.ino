#define IRDetector /* pin num */
int IREmitter = ;

void setup() {
  pinMode(IREmitter, OUTPUT);
  pinMode(IRDetector, INPUT);
//Serial.begin(9600);
}

void shineIR() {
  digitalWrite(IREmitter, HIGH);
}

//might need to determine the (range of?) intensity_diff & the value of distance when mbot is parallel to the wall
//if the distance returned is > or < than that of parallel's, nudge left or right

double read_ir_distance() {
  digitalWrite(IREmitter, LOW); // get a reference reading for the ambient IR level
  delay(1000); // might need to adjust
  double reference_reading = analogRead(IRDetector);
  
  digitalWrite(IREmitter, HIGH); // turn on emitter to read the IR detector again to obtain the signal reading including both the emitted and ambient IR.
  delay(1000); 
  double signal_reading = analogRead(IRDetector);
  double intensity_diff = reference_reading - signal_reading; //not sure which is higher
  double distance = map(intensity_diff, 0, 1023, 0, 100);  //map(value, fromLow, fromHigh, toLow, toHigh)

  return distance;
}
  
  
