bool isNearIR() {
  shineRed(); // turn off IR Emitter
  long baseVal = analogRead(IR);
  shineIR(); 
  long val = analogRead(IR);
  long diff = baseVal - val;
  
  /* 
   * Check if the baseline ambient IR and its voltage drop fall within the thresholds 
   * This is established based on the lookup table for a distance less than 4 cm 
   */
  if (baseVal >= 380 && baseVal <= 480) {
    if (diff >= 141 && diff <= 210) {
      return true;
    }
  }

  if ( baseVal >= 510 && baseVal <= 740) {
    if (diff >= 210 && diff <= 350) {
      return true;
    }
  }
  
  if (baseVal >= 870 && baseVal <= 905) {
    if (diff >= 610 && diff <= 670) {
      return true;
    }
  }
  
  // If none of the conditions are met, distance > 4cm ! 
  return false; 
}
