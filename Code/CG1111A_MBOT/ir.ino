// new function
bool ir_sensing_distance() {
  shineRed();//turn off IR Emitter
  long baseline = analogRead(IR);
  shineIR();//turn on IR Emitter
  long emitted_reading = analogRead(IR);
  long diff = baseline - emitted_reading;

//result based on calibration on Wed studio
//2cm
  if (baseline >= 510 && baseline <= 540) {
    if (diff >= 215 && diff <= 225 ) {
      return true;
    }
  } 

//2cm
  if (baseline >= 630 && baseline <= 659) {
    if(diff >= 301 && diff <= 309) {
      return true;
    }
  }

//3cm
  if (baseline >= 380 && baseline <= 480) {
    if ((diff >= 190 && diff <= 210) || (diff >= 141 && diff <= 160)) {
      return true;
    }
  }
//4cm
  /*  if (diff >= 141 && diff <= 160) { //need to double check for this
      return true;
    }
  } */

//5cm ++
/*  if (baseline >= 460 && baseline <= 505) {
    if (diff >= 135 && diff <= 140) {
      return false;
    }
  }*/
  return false; 
}
