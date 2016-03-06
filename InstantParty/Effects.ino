void swirl(){
  for (int i = 0; i<20;i++){
    strip.setPixelColor(i,realRed, realGreen, realBlue);
    strip.show();
    delay(DMX_EffectParameter);
  }
  setAllBlack();
}

void black(boolean once){
  setAllBlack();
  while(effect == BLACK){
    delay(20);
    if (once) break;
  }
}

void blinky(boolean once){
  // while (effect == BLINK){
  delay(500);
  setAllColor(realRed, realGreen, realBlue);
  delay(500);
  setAllBlack();
  // if (once) break;
  // }

}

void color(boolean once){

  // while(effect == COLOR){
  //delayPoll(10);
  // setAllHSV(realRed, realGreen, realBlue);

  setAllColor(realRed, realGreen, realBlue);
  // delay(20);
  //   if (once) break;
  // }
}

void strobe(boolean once){
  // while(effect == STROBE){
  //setAllColor(255,255,255);
  int i = 0;
  int maxi = random (10,30);
  while (i<maxi){
    setAllColor(realRed, realGreen, realBlue);
    delay(5);
    setAllBlack();
    delay(100);
    i++;
  }
  //if (once) break;
  // }
}

void rainbow(boolean once){
  while(effect == RAINBOW){
    rainbowCycle(2,brightness/4);
    if (once) break;
  }
}

void rainbowfill(boolean once){
  int i;
  setAllBlack();
  while(effect == RAINBOWFILL){
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(i*10,brightness));
      strip.show();
      delay(DMX_EffectParameter);
    }
    setAllBlack();
    if (once) break;
  }
}

void rainbowsweep(boolean once){
  int i;
  setAllBlack();
  while(effect == RAINBOWSWEEP){
    for (i=0; i < 20; i++) {
      strip.setPixelColor(i, Wheel(i*10,brightness));
      strip.setPixelColor(40-i, Wheel(i*10,brightness));

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
    if (once) break;
  }
}


void sparkle(boolean once){
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
    if (once) break;
  }
}


void rainbowsparkle(boolean once){
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
          strip.setPixelColor(i,Wheel(random(255),brightness*bright));
          strip.setPixelColor(40-i,Wheel(random(255),brightness*bright));

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
    if (once) break;
  }
}

void wobble (boolean once){
  float dots [strip.numPixels()+4];

  while(effect == WOBBLE){

    for (int i = 0; i<strip.numPixels();i++){
      for (int i = 0;i < strip.numPixels()+4;i++)dots[i]=0.0;
      dots[i+2]=1.0;
      dots[i+1]=0.5; 
      dots[i+3]=0.5;
      dots[i]=0.05;
      dots[i+4]=0.05;
      for (int i = 0;i < strip.numPixels();i++){
        strip.setPixelColor(i,Color(realRed,realGreen,realBlue,brightness*dots[i+2]));
      }
      strip.show();
      int dist = i-(strip.numPixels()/2);
      int dist1 = abs(dist);
      float speedmod = 0.1+float(float(dist1)/float(strip.numPixels()/2));
      delay(int(float(DMX_EffectParameter)*speedmod));
    }
    for (int i = strip.numPixels()-1; i>0;i--){
      for (int i = 0;i < strip.numPixels()+4;i++)dots[i]=0.0;
      dots[i+2]=1.0;
      dots[i+1]=0.5; 
      dots[i+3]=0.5;
      dots[i]=0.05;
      dots[i+4]=0.05;
      for (int i = 0;i < strip.numPixels();i++){
        strip.setPixelColor(i,Color(realRed,realGreen,realBlue,brightness*dots[i+2]));
      }
      strip.show();
      int dist = i-(strip.numPixels()/2);
      int dist1 = abs(dist);
      float speedmod = 0.1+float(float(dist1)/float(strip.numPixels()/2));
      delay(int(float(DMX_EffectParameter)*speedmod));
    }
    if (once) break;
  }
}

/* Helper functions */
void setAllColor(int red, int green, int blue){
  for (int i = 0; i<strip.numPixels();i++){
    strip.setPixelColor(i,red,green,blue);
  }
  strip.show();
}


void setAllHSV(unsigned int red, unsigned int green, unsigned int blue){
  for (int i = 0; i<strip.numPixels();i++){
    strip.setPixelColor(i,hsv(red,green,blue));
  }
  strip.show();
}


void setAllBlack(){
  for (int i = 0; i<strip.numPixels();i++){
    strip.setPixelColor(i, 0,0,0);
  }
  strip.show();
}


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

void rainbowCycle(uint8_t wait,float b) {
  int i, j;

  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256, b) );
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
uint32_t Wheel(byte WheelPos, float b)
{
  if (WheelPos < 85) {
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0,b);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(255 - WheelPos * 3, 0, WheelPos * 3,b);
  } 
  else {
    WheelPos -= 170; 
    return Color(0, WheelPos * 3, 255 - WheelPos * 3,b);
  }
}

void delayPoll(int milliseconds){
  for (int i = 0; i < milliseconds; i++){
    delay(1);
    if (effectHasChanged){
      selectEffect(true);  
    }
  }
}





