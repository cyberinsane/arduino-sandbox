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
int loopOne[4] = {27, 28, 35, 36};
int loopTwo[12] = {18, 19, 20, 21, 29, 37, 45, 44, 43, 42, 34, 26};
int loopThree[20] = {9, 10, 11, 12, 13, 14, 17, 25, 33, 41, 49, 50, 51, 52, 53, 54, 46, 38, 30, 22};
int loopFour[28] = {0, 1, 2, 3, 4, 5, 6, 7,  15, 23, 31, 39, 47, 55, 63, 56, 57, 58, 59, 60, 61, 62, 8, 16, 24, 32, 40, 48};

void setup() {
  Serial.begin(57600);
  Serial.println("resetting");
  LEDS.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  LEDS.setBrightness(100);

  fadeall();
  FastLED.show();
}

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(255, 92, 0);
  }
}

void showLoopOne() {
  for (int i = 0; i < 4; i++) {
    leds[loopOne[i]] = CRGB::LightSeaGreen;
    // leds[loopOne[i]].setRGB(255, 92, 0);
  }
}

void showLoopTwo() {
  for (int i = 0; i < 12; i++) {
    // leds[loopTwo[i]].setRGB(255, 92, 0);
    leds[loopTwo[i]] = CRGB::Cyan;
  }
}

void showLoopThree() {
  for (int i = 0; i < 20; i++) {
    // leds[loopThree[i]].setRGB(255, 92, 0);
    leds[loopThree[i]] = CRGB::LightSeaGreen;
  }
}

void showLoopFour() {
  for (int i = 0; i < 28; i++) {
    leds[loopFour[i]] = CRGB::Purple;
  }
}


void loop() {

  // fadeall();

  //  sensorValue = analogRead(sensorPin);
  //
  //   if (sensorValue > 200) {
  //    showLoopOne();
  //
  //    if (sensorValue > 270) {
  //      showLoopTwo();
  //    }
  //
  //    if (sensorValue > 320) {
  //      showLoopThree();
  //    }
  //
  //    if (sensorValue > 400) {
  //      showLoopFour();
  //    }
  //
  //  static uint8_t hue = 0;
  //  // random colored speckles that blink in and fade smoothly
  //  fadeToBlackBy(leds, NUM_LEDS, 10);
  //  int pos = random16(NUM_LEDS);
  //  leds[pos].setRGB(255,255,255);

  // FastLED.show();
  //delay(50);
}

