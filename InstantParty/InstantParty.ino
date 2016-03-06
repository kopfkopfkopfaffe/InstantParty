// TODO
// *   Ensure short reaction times in looping effects:
//        Implement own delay loop that checks frequently if effect variable is changed.
//        If so, the function that uses the delay variable breaks and the effect selecter
//        is called. The effect selecter should not be called uppon effect selection via DMX. (change that!)
// *   If brightness is changed, readjust realRGB
// DMX CHANNELS:
// 0: Red               Color chan Red
// 1: Green             Color chan Green
// 2: Blue              Color chan Blue
// 3: Brightness        Is multiplied with colors
// 4: Effect            Loops an Effect
// 5: Effect Parameter  Chilldown time, etc.  
// 6: Bang              Triggers an Effect only ONCE
// 7: Base Red          Color of the internal LEDs
// 8: Base Green        Color of the internal LEDs
// 9: Base Blue         Color of the internal LEDs

#include "SPI.h"
#include "Adafruit_WS2801.h"

// WS2801 definitions
// ### Adjust these to your hardware! ###
uint8_t dataPin  = 3;
uint8_t clockPin = 2;
uint8_t segments = 3; // Number of stripe segments
uint8_t LpS = 20; // Numberof LEDs per Segment

// Potentiometer pin definitions
// ### Adjust these to your hardware! ###
uint8_t speedPot = A0; // adjust the effect speed
uint8_t gayPot = A1; // adjust the width of the color selection on the hue scale
uint8_t huePot = A2; // adjust the center of the color selection on the hue scale
uint8_t wildPot = A3; // adjust the wildness of animation selection

// Control variables
uint8_t velocity = 0;
uint8_t gayness = 0;
uint8_t hue = 0;
uint8_t wildness = 0;

uint8_t brightness = 255;
uint8_t saturation = 255;

// Effect numbers
#define RGB 0
#define STROBE 1
#define RAINBOW 2
#define CHASER 3
#define SPARKLE 4
#define BLACK 5
#define COLOR 6
#define BLINK 7
#define RAINBOWFILL 8
#define RAINBOWSWEEP 9
#define RAINBOWSPARKLE 10
#define WOBBLE 11

// Mode numbers
#define LOOP 1
#define BANG 2
// Program Flow 'n' Shit
//uint8_t effect = RAINBOWSWEEP;
//uint8_t effect = COLOR;
//uint8_t effect = STROBE;

uint8_t effect = WOBBLE;
//uint8_t effect = RAINBOWSPARKLE;
boolean effectHasChanged = false;
int scheduledEffect = 0;
float brightness = 1.0;
// realColors are multiplied with brightness
unsigned int realRed =0;
unsigned int realGreen = 255;
unsigned int realBlue = 255;
// Configure a DMX slave controller


uint8_t DMX_Brightness = 15;
uint8_t DMX_Effect = 0;                    //efffect
uint8_t DMX_EffectParameter = 30;  //timing
uint8_t DMX_Bang = 0;


// Configure the LED Strip
Adafruit_WS2801 strip = Adafruit_WS2801(40, dataPin, clockPin);

// the setup routine runs once when you press reset:
void setup() {             


  // Enable LED stip
  strip.begin();
  // Update LED contents, to start they are all 'off'
  strip.show();

  selectEffect(true);
}

// the loop routine runs over and over again forever:
void loop() 
{
  //analogWrite(LED_B,128);
  //setAllColor();
  //strip.show();
  //strobe(false); 
  //color(false);
  //  for (int i = 0;i<360;i++){
  //    realRed =i;
  selectEffect(true);
  setEffectRandom();
  setColorsRandom();
  // delay(500);
  //  }
  // selectEffect(false);
  // blinky(false);
}


void selectEffect(boolean once){
  //analogWrite(LED_G, random(255));
  if (effect == STROBE) strobe(once);
  else if (effect == RAINBOW) rainbow(once);
  else if (effect == BLACK) black(once);
  else if (effect == COLOR) color(once);
  else if (effect == SPARKLE) sparkle(once);
  //else if (effect == RGB) rgb (once);
  else if (effect == BLINK) blinky(once);
  else if (effect == RAINBOWFILL) rainbowfill(once);
  else if (effect == RAINBOWSWEEP) rainbowsweep(once);
  else if (effect == RAINBOWSPARKLE) rainbowsparkle(once);
  else if (effect == WOBBLE) wobble(once);
}





void setEffectRandom(){
  int rnd = random(16);
  if (rnd ==1)effect = RAINBOWSWEEP;
  if (rnd ==2)effect = WOBBLE;
  if (rnd ==3)effect = RAINBOWSWEEP;
  if (rnd ==4)effect = WOBBLE;
  if (rnd ==5)effect = WOBBLE;
  if (rnd ==6)effect = WOBBLE;
  if (rnd ==7)effect = RAINBOWSWEEP;
  if (rnd ==8)effect = WOBBLE;
  if (rnd ==9)effect = RAINBOWSPARKLE;
  if (rnd ==10)effect = STROBE;
  if (rnd ==11)effect = WOBBLE;
  if (rnd ==12)effect = WOBBLE;
  if (rnd ==13)effect = STROBE;
  if (rnd ==14)effect = STROBE;
  if (rnd ==15)effect = WOBBLE;
}




void setColorsRandom(){
  int rnd = random(7);
  if (rnd ==1){
    realRed =255;
    realGreen = 0;
    realBlue = 255;
  } 
  if (rnd ==2){
    realRed =0;
    realGreen = 255;
    realBlue = 255;
  } 
  if (rnd ==3){
    realRed =0;
    realGreen = 255;
    realBlue = 0;
  } 
  if (rnd ==4){
    realRed =255;
    realGreen = 255;
    realBlue = 0;
    realGreen = 0;
    realBlue = 0;
  } 
  if (rnd ==6){
    realRed =0;
    realGreen = 0;
    realBlue = 255;
  } 
  if (rnd ==5){
    realRed =255;
    realGreen = 0;
    realBlue = 0;
  } 
  if (rnd ==6){
    realRed =0;
    realGreen = 0;
    realBlue = 255;
  } 



}









