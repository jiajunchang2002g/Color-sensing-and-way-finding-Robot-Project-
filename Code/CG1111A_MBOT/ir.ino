// new function
bool ir_sensing_distance() {
  shineRed();//turn off IR Emitter
  long baseline = analogRead(IR);
  shineIR();//turn on IR Emitter
  long emitted_reading = analogRead(IR);
  long diff = baseline - emitted_reading;
  return false;
  if (baseline >= 380 && baseline <= 480) {
    if (diff >= 141 && diff <= 210) {
      return true;
    }
  }

  if (baseline >= 510 && baseline <= 740) {
    if((diff >= 210 && diff <= 350)) {
      return true;
    }
  }
  
  if (baseline >= 870 && baseline <= 905) {
    if (diff >= 610 && diff <= 670) {
      return true;
    }
  }

  return false; //distance > 4cm
}
