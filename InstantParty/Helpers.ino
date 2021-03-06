// Helper functions



// put in HSV, receive a 32-bit RGB color that you can feed into setPixelColor()
uint32_t hsv(unsigned int hue, unsigned int sat, unsigned int val){
  uint32_t myHsv;
  // overwritten by global variables
  //val = brightness;
  sat = saturation;

  unsigned char r,g,b;
  unsigned int H_accent = hue/60;
  unsigned int bottom = ((255 - sat) * val)>>8;
  unsigned int top = val;
  unsigned char rising  = ((top-bottom)  *(hue%60   )  )  /  60  +  bottom;
  unsigned char falling = ((top-bottom)  *(60-hue%60)  )  /  60  +  bottom;

  switch(H_accent) {
  case 0:
    r = top;
    g = rising;
    b = bottom;
    break;

  case 1:
    r = falling;
    g = top;
    b = bottom;
    break;

  case 2:
    r = bottom;
    g = top;
    b = rising;
    break;

  case 3:
    r = bottom;
    g = falling;
    b = top;
    break;

  case 4:
    r = rising;
    g = bottom;
    b = top;
    break;

  case 5:
    r = top;
    g = bottom;
    b = falling;
    break;
  }
  myHsv = rgb(r,g,b);
  return myHsv;
}

// create a 24 bit color value from R,G,B
uint32_t rgb(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

// Create a 24 bit color value from R,G,B,Brightness
uint32_t rgb(byte r, byte g, byte b, float br)
{
  r = byte(r * br);
  g = byte(g * br);
  b = byte(b * br);

  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

// select hue randomly around center hue with spread of gayness
uint32_t randomColor(){
  uint32_t c;
  // get random number in range gayness
  signed int tmpHue = random (0,gayness);
  // center gayness around 0
  tmpHue = tmpHue - (gayness/2);
  // modify by global hue > get hue += random(gayness/2)
  tmpHue += hue;
  unsigned int myHue = 0;
  // adjust hue to 0-360
  if (tmpHue < 0) myHue = 360 + tmpHue;
  else if(tmpHue > 359) myHue =  tmpHue - 360;
  else myHue = tmpHue;
  c = hsv(myHue,255,255);
  return c;
}

// select hue randomly around center hue with spread of gayness
uint32_t randomColor(uint8_t brightness){
  uint32_t c;
  // get random number in range gayness
  signed int tmpHue = random (0,gayness);
  // center gayness around 0
  tmpHue = tmpHue - (gayness/2);
  // modify by global hue > get hue += random(gayness/2)
  tmpHue += hue;
  unsigned int myHue = 0;
  // adjust hue to 0-360
  if (tmpHue < 0) myHue = 360 + tmpHue;
  else if(tmpHue > 359) myHue =  tmpHue - 360;
  else myHue = tmpHue;
  c = hsv(myHue,255,brightness);
  return c;
}

// set all pixels to the given color
void setAllColor(uint32_t myColor){
  for (int i = 0; i<strip.numPixels();i++){
    strip.setPixelColor(i,myColor);
  }
  strip.show();
}

// set all pixels in a segment to given color
void setSegmentColor(int mySegment, uint32_t myColor){
  for (int i = mySegment*LpS; i< mySegment +1 * LpS;i++){
    strip.setPixelColor(i,myColor);
  }
  strip.show();
}

// set all pixels black
void setAllBlack(){
  for (int i = 0; i<strip.numPixels();i++){
    strip.setPixelColor(i, 0,0,0);
  }
  strip.show();
}

