long ir_sensing_distance() {
  shineRed();//turn off IR Emitter
  long baseline = analogRead(IR);
  shineIR();//turn on IR Emitter
  long emitted_reading = analogRead(IR);
  long diff = baseline - emitted_reading;

//result based on calibration on Wed studio
  if (baseline >= 510 && baseline <= 540) {
    if (diff >= 215 && diff <= 225 ) {
      return 2;//estimated distance;
    }
  } 

  if (baseline >= 630 && baseline <= 659) {
    if(diff >= 301 && diff <= 309) {
      return 2;
    }
  }

  if (baseline >= 380 && baseline <= 480) {
    if (diff >= 190 && diff <= 210) {
      return 3;
    }

    if (diff >= 141 && diff <= 160) { //need to double check for this
      return 4;
    }
  }

  if (baseline >= 460 && baseline <= 505) {
    if (diff >= 135 && diff <= 140) {
      return 5;
    }
  }
  return ; //havent completed for now
}
