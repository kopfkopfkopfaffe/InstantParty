
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
uint8_t velocity = 100;
uint16_t gayness =  360;
uint16_t hue = 150;
uint8_t wildness = 10;

float brightness = 1.0;
unsigned int saturation = 255;

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
#define EXPLODE 12
#define GLARE 13  

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
Adafruit_WS2801 strip = Adafruit_WS2801(segments * LpS, dataPin, clockPin);

void setup() {             
  strip.begin();
  Serial.begin(9600);
 // delay (5000);
  strip.show();
  selectEffect();

}

void loop() 
{
  //selectEffect();
  // setEffectRandom();
  // setColorsRandom();

  colorize();
  delay(10);
  hue ++;
  if(hue >359)hue = 0;
}


void selectEffect(){
  if (effect == STROBE) strobe();
  else if (effect == RAINBOW) rainbow();
  else if (effect == BLACK) black();
  else if (effect == COLOR) colorize();
  else if (effect == SPARKLE) sparkle();
  //else if (effect == RGB) rgb (once);
  else if (effect == BLINK) blinky();
  else if (effect == RAINBOWFILL) rainbowfill();
  else if (effect == RAINBOWSWEEP) rainbowsweep();
  else if (effect == RAINBOWSPARKLE) rainbowsparkle();
  else if (effect == WOBBLE) wobble();
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










