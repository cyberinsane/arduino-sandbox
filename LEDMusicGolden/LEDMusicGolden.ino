#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 64

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7

int sensorPin = A4;
int sensorValue = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];
int loopOne[4] = {28,29,36,37};
int loopTwo[12] = {19,20,21,22,27,35,43,44,45,46,38,30};
int loopThree[20] = {10,11,12,13,14,15,23,31,39,47,55,54,53,52,51,50,42,34,26,18};
int loopFour[28] = {1,2,3,4,5,6,7,8,16,24,32,40,48,56,64,63,62,61,60,59,58,57,49,41,33,25,17,9};

void setup() {
  Serial.begin(57600);
  Serial.println("resetting");
  LEDS.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  LEDS.setBrightness(84);
}

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

void showLoopOne() {
  for (int i = 0; i < 4; i++) {
    leds[loopOne[i] -1] = CRGB::Red;
  }
}

void showLoopTwo() {
  for (int i = 0; i < 12; i++) {
    // leds[loopTwo[i]].setRGB(255, 0, 0);
    leds[loopTwo[i] -1] = CRGB::Blue;
  }
}

void showLoopThree() {
  for (int i = 0; i < 20; i++) {
    // leds[loopThree[i]] = CRGB::Blue;
    leds[loopThree[i] -1].setRGB(255, 92, 0);
  }
}

void showLoopFour() {
  for (int i = 0; i < 28; i++) {
    leds[loopFour[i] -1] = CRGB::Green;
    // leds[loopFour[i]].setRGB(255, 92, 0);
  }
}


void loop() {

  // fadeall();

  sensorValue = analogRead(sensorPin);

  if (sensorValue > 180) {
    showLoopOne();

    if (sensorValue > 280) {
      showLoopTwo();
    }

    if (sensorValue > 320) {
      showLoopThree();
    }

    if (sensorValue > 400) {
      showLoopFour();
    }

//  static uint8_t hue = 0;
//  // random colored speckles that blink in and fade smoothly
//  fadeToBlackBy(leds, NUM_LEDS, 10);
//  int pos = random16(NUM_LEDS);
//  leds[pos].setRGB(255,255,255);

    FastLED.show();
    delay(50);

  }
  else {
    fadeall();
    FastLED.show();
  }

}

