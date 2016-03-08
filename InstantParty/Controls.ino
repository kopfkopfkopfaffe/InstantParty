// read all potentiometers, adjust values
void checkPots(){
  velocity = map(analogRead(speedPot),0,1023,0,255);
  gayness = map(analogRead(gayPot),0,1023,0,360);
  hue = map(analogRead(huePot),0,1023,0,255);
  wildness = map(analogRead(wildPot),0,1023,0,255);
}

// delay that still accepts inputs while waiting
void iDelay(int milliseconds){
  for (int i = 0;i<milliseconds;i++){
    checkPots();
    delay(1);
  }
}

