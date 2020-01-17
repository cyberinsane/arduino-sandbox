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
    leds[dot] = CHSV(hue++, 255, 255);
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
  }


  
//
//
//  for(int i = 0; i < NUM_LEDS; i++) {
//    // Set the i'th led to red 
//    leds[i] = CRGB::Yellow;
//    // Show the leds
//    // now that we've shown the leds, reset the i'th led to black
//    // leds[i] = CRGB::Black;
//    // Wait a little bit before we loop around and do it again
//    // delay(10);
//  }

//
//leds[14] = CRGB::Yellow;
//leds[13] = CRGB::Yellow;
//leds[18] = CRGB::Yellow;
//leds[17] = CRGB::Yellow;
//
//leds[46] = CRGB::Yellow;
//leds[49] = CRGB::Red;
//leds[45] = CRGB::Yellow;
//leds[50] = CRGB::Yellow;
//
//leds[10] = CRGB::Yellow;
//// leds[9] = CRGB::Yellow;
//leds[21] = CRGB::Yellow;
////leds[22] = CRGB::Yellow;
//leds[26] = CRGB::Yellow;
//leds[25] = CRGB::Yellow;
//
//leds[37] = CRGB::Yellow;
// leds[38] = CRGB::Yellow;
//leds[42] = CRGB::Yellow;
// leds[41] = CRGB::Yellow;
//
//leds[53] = CRGB::Yellow;
// leds[54] = CRGB::Yellow;
//leds[9] = CRGB::Yellow;
//leds[22] = CRGB::Yellow;



//leds[18] = CRGB::Yellow;
//leds[7] = CRGB::Yellow;
//leds[9] = CRGB::Yellow;
//leds[10] = CRGB::Yellow;


FastLED.show();
delay(30);

}
