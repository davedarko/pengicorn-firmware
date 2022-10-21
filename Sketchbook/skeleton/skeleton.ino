
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define SDA_PIN 4
#define SCL_PIN 5

#define DISPLAY_ADDRESS  0x3C // SH1106
#define PCF8574          0x38
#define AVRTOUCH         0x11


#define LEFT_EYE 0
#define RIGHT_EYE 1
#define NEOPIXEL_PIN 0
#define NEOPIXEL_CNT 2

Adafruit_NeoPixel strip(NEOPIXEL_CNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// use the frame buffer or U8x8 versions for ESP8266, page buffer does not work
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:

  u8g2.begin();

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)

  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip.show();
  strip.setPixelColor(LEFT_EYE, strip.Color(127, 0, 0));
  strip.setPixelColor(RIGHT_EYE, strip.Color(0, 127, 0));
  strip.show();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_10x20_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  u8g2.drawStr( 0, 0, "@davedarko");
  u8g2.drawStr( 0, 20, "#supercon22");
  u8g2.sendBuffer();
  delay(100);
  
  // put your main code here, to run repeatedly:
  //  strip.setPixelColor(LEFT_EYE, strip.Color(127, 0, 0));
  //  strip.setPixelColor(RIGHT_EYE, strip.Color(0, 127, 0));
  //  strip.show();
}
