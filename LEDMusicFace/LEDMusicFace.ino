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
int loopOne[16] = {17, 18, 19, 21, 22, 23, 26, 30, 36, 41, 50, 51, 52, 53, 54, 47};
int loopTwo[15] = {10, 17, 18, 19, 21, 22, 23, 14, 49, 42, 43, 44, 45, 46, 55};
int loopThree[16] = {16, 17, 18, 19, 20, 21, 22, 23, 26, 29, 49, 50, 51, 52, 53, 54};
int loopFour[28] = {16, 9, 18, 21, 14, 23, 50, 43, 52, 45, 31, 39, 47, 55, 63, 56, 57, 58, 59, 60, 61, 62, 8, 16, 24, 32, 40, 48};

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
    leds[loopOne[i]].setRGB(255, 92, 0);
  }
}

void showLoopTwo() {
  for (int i = 0; i < 12; i++) {
    leds[loopTwo[i]].setRGB(255, 92, 0);
    // leds[loopTwo[i]] = CRGB::Green;
  }
}

void showLoopThree() {
  for (int i = 0; i < 20; i++) {
    leds[loopThree[i]].setRGB(255, 92, 0);
  }
}

void showLoopFour() {
  for (int i = 0; i < 28; i++) {
    
    leds[loopFour[i]].setRGB(255, 92, 0);
  }
}


void loop() {

  // fadeall();

  sensorValue = analogRead(sensorPin);

  if (sensorValue > 200) {
    showLoopOne();

    if (sensorValue > 270) {
      showLoopTwo();
    }

    if (sensorValue > 320) {
      showLoopThree();
    }

    if (sensorValue > 400) {
      showLoopFour();
    }

  static uint8_t hue = 0;
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos].setRGB(255,255,255);

    FastLED.show();
    delay(50);

  }
  else {
    fadeall();
    FastLED.show();
  }

}

