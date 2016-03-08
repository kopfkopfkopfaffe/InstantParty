void swirl(){
  for (int i = 0; i<20;i++){
    strip.setPixelColor(i,realRed, realGreen, realBlue);
    strip.show();
    delay(DMX_EffectParameter);
  }
  setAllBlack();
}

void black(){
  setAllBlack();
  while(effect == BLACK){
    iDelay(20);
  }
}

void blinky(){
  while (effect == BLINK){
    iDelay(2 * 270 - velocity);
    setAllColor(randomColor());
    iDelay(2 * 270 - velocity);
    setAllBlack();
  }
}

void colorize(){
  while (effect == COLOR){
    setAllColor(randomColor());
  }
}

// strobelight. the wilder, the longer. different for each segment
void strobe(){
  int i = 0;
  int maxi = random (10,wildness/2);
  while (i<maxi){
    for (int i = 0; i < segments;i++){
      setSegmentColor(i,randomColor());
    }
    iDelay(5+(25-velocity/10));
    setAllBlack();
    iDelay(100+(25-velocity/10));
    i++;
  }
}

void rainbow(){
  while(effect == RAINBOW){
    rainbowCycle(2,brightness/4);
  }
}

void rainbowfill(){
  int i;
  setAllBlack();
  while(effect == RAINBOWFILL){
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(i*10));
      strip.show();
      delay(DMX_EffectParameter);
    }
    setAllBlack();
  }
}

void rainbowsweep(){
  int i;
  setAllBlack();
  while(effect == RAINBOWSWEEP){
    for (i=0; i < 20; i++) {
      strip.setPixelColor(i, Wheel(i*10));
      strip.setPixelColor(40-i, Wheel(i*10));

      strip.show();
      delay(DMX_EffectParameter);
    }
    for (i=0; i < 20; i++) {
      strip.setPixelColor(i,0);
      strip.setPixelColor(40-i,0);
      strip.show();
      delay(DMX_EffectParameter);
    }
    setAllBlack();
  }
}


void sparkle(){
  int sparks [strip.numPixels()];
  while(effect == SPARKLE){
    setAllBlack();
    for (int i = 0;i < strip.numPixels();i++)sparks[i]= (-1);
    boolean running = true;
    /*
     * An array holds the states of each pixel which is initially -1, inactive
     * by random, a pixel is selected. if it is inactive, it is put to full brightness.
     * each pixel that is active fades down during each loop.
     * if all pixels have burned and faded down, stop
     */
    while (running == true){
      // try to light new sparks

      //int counter = 0;
      //while (sparks[i]<0){
      //if (counter > strip.numPixels())break;
      //i = random (strip.numPixels());
      //counter ++;
      //}
      int y = random(strip.numPixels());
      //int b = random(10);
      if (sparks[y]<0)sparks[y]=250; 

      // render effect frame
      int sum = 0;
      for (int i = 0;i < strip.numPixels();i++){

        if (sparks[i]>-1){ 
          int red = float(realRed) * (250.0/sparks[i]);
          int green = float(realGreen) * (250.0/sparks[i]);
          int blue = float(realBlue) * (250.0/sparks[i]);
          strip.setPixelColor(i,red,green,blue);
          //strip.setPixelColor(i,sparks[i],sparks[i],sparks[i]);
          strip.show();
          // age sparks
          if (sparks[i]>0)sparks[i] = sparks [i]-50;
          sum = sum + sparks[i];
        }
      }
      delay(DMX_EffectParameter);
      if (sum==0){ 
        running = false;
        setAllBlack();
      }
    }
  }
}


void rainbowsparkle(){
  int sparks [strip.numPixels()];
  while(effect == RAINBOWSPARKLE){
    setAllBlack();
    for (int i = 0;i < strip.numPixels();i++)sparks[i]= (-1);
    boolean running = true;
    /*
  * An array holds the states of each pixel which is initially -1, inactive
     * by random, a pixel is selected. if it is inactive, it is put to full brightness.
     * each pixel that is active fades down during each loop.
     * if all pixels have burned and faded down, stop
     */
    while (running == true){
      // try to light new sparks

      //int counter = 0;
      //while (sparks[i]<0){
      //if (counter > strip.numPixels())break;
      //i = random (strip.numPixels());
      //counter ++;
      //}
      int y = random(strip.numPixels());
      //int b = random(10);
      if (sparks[y]<0)sparks[y]=250; 

      // render effect frame
      int sum = 0;
      for (int i = 0;i < strip.numPixels();i++){

        if (sparks[i]>-1){ 
          float bright = sparks[i]/250.0;
          strip.setPixelColor(i,Wheel(random(255)));
          strip.setPixelColor(40-i,Wheel(random(255)));

          //strip.setPixelColor(i,sparks[i],sparks[i],sparks[i]);
          strip.show();
          // age sparks
          if (sparks[i]>0)sparks[i] = sparks [i]-50;
          sum = sum + sparks[i];
        }
      }
      delay(3);
      if (sum==0){ 
        running = false;
        setAllBlack();
      }
    }
  }
}

void wobble (){
  // array of brightness adjustment 
  float dots [LpS+4];
  while(effect == WOBBLE){
    // generate a random color and pick components
    uint32_t myColor = randomColor();
    uint8_t myBlueRed = myColor;
    uint8_t myGreen = myColor >>= 8;
    uint8_t myRed = myColor >>= 16;

    // move dot to the right over all pixels of the segment
    for (int i = 0; i<LpS;i++){
      // set all pixels to black
      for (int i = 0;i < LpS+4;i++)dots[i]=0.0;
      // set the brightness at the dot center to full.
      // set pixels around it a little dimmer
      dots[i+2]=1.0;
      dots[i+1]=0.5; 
      dots[i+3]=0.5;
      dots[i]=0.05;
      dots[i+4]=0.05;
      // for all segments
      for (int j = 0;j<segments +1;j++){
        // render all pixels in segment
        for (int i = j * LpS; i < (j*LpS)+LpS;i++){
          strip.setPixelColor(i,rgb(realRed,realGreen,realBlue,brightness*dots[i+2]));
        }
      }
      strip.show();
      int dist = i-(LpS/2);
      int dist1 = abs(dist);
      float speedmod = 0.1+float(float(dist1)/float(LpS/2));
      iDelay(int(float(velocity)*speedmod));
    }


    // move dot back to the left over all pixels of the segment
    for (int i = LpS-1; i>0;i--){
      // for all pixels in the dot...
      for (int i = 0;i < LpS+4;i++)dots[i]=0.0;
      dots[i+2]=1.0;
      dots[i+1]=0.5; 
      dots[i+3]=0.5;
      dots[i]=0.05;
      dots[i+4]=0.05;
      // for all segments
      for (int j = 0;j<segments +1;j++){
        // render all pixels in segment
        for (int i = j * LpS; i < (j*LpS)+LpS;i++){
          strip.setPixelColor(i,rgb(realRed,realGreen,realBlue,brightness*dots[i+2]));
        }
      }
      strip.show();
      int dist = i-(LpS/2);
      int dist1 = abs(dist);
      float speedmod = 0.1+float(float(dist1)/float(LpS/2));
      iDelay(int(float(velocity)*speedmod));
    }
  } 
}

/* Helper functions */


/*
void setPixels(int count){
 for (int i = 0; i<20;i++){
 strip.setPixelColor(i, 0,0,0);
 }
 strip.show();
 for (int i = 0; i<count;i++){
 strip.setPixelColor(i, 45,0,255);
 }
 strip.show();
 }
 */

void rainbowCycle(uint8_t wait,float b) {
  int i, j;

  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}




//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return rgb(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return rgb(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170; 
    return rgb(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}









