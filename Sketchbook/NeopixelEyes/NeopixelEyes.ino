#include <Adafruit_NeoPixel.h>

#define LEFT_EYE 0
#define RIGHT_EYE 1
#define NEOPIXEL_PIN 0
#define NEOPIXEL_CNT 2

Adafruit_NeoPixel strip(NEOPIXEL_CNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)

  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip.show();
  strip.setPixelColor(LEFT_EYE, strip.Color(127, 0, 0));
  strip.setPixelColor(RIGHT_EYE, strip.Color(0, 127, 0));
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  strip.setPixelColor(LEFT_EYE, strip.Color(127, 0, 0));
  //  strip.setPixelColor(RIGHT_EYE, strip.Color(0, 127, 0));
  //  strip.show();
}
