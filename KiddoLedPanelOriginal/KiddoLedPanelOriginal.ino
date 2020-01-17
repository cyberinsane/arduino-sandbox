#include <FastLED.h>

#define NUM_LEDS 64
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}
void loop() {

  static uint8_t hue = 0;
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    // Set color from Hue, Saturation, and Value.  
  // Conversion to RGB is automatic.
  leds[dot] = CHSV(255, 190, 1);
  leds[dot].setHue(10);
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
  }

//
//int savedIndex = 0;
//  for (int dot = 0; dot < NUM_LEDS; dot++) {
//    // Set color from Hue, Saturation, and Value.  
//  // Conversion to RGB is automatic.
//  int requiredDot = dot*8;
//
//  leds[requiredDot] = CHSV(255, 190, 1);
//  leds[requiredDot].setHue(10);
//    FastLED.show();
//  requiredDot = dot+8;
//    // clear this led for the next time around the loop
//    leds[requiredDot] = CRGB::Black;
//    delay(30);
//  }
//




// FastLED.show();
delay(30);

}
