
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define SDA_PIN 4
#define SCL_PIN 5

#define DISPLAY_ADDRESS  0x3C // SH1106
#define PCF8574A         0x38 // PCF8574A has different range than PCF8574
#define AVRTOUCH         0x11
#define GUY_FAWKES       0x50

#define LEFT_EYE 0
#define RIGHT_EYE 1
#define NEOPIXEL_PIN 0
#define NEOPIXEL_CNT 2

#define BUTTON_UP    B10000000
#define BUTTON_DOWN  B00100000
#define BUTTON_LEFT  B01000000
#define BUTTON_RIGHT B00010000
#define BUTTON_A     B00000100
#define BUTTON_B     B00001000
#define BUTTON_C     B00000001
#define BUTTON_SD    B00000010

boolean bottonU_pressed = false;
boolean bottonD_pressed = false;
boolean bottonL_pressed = false;
boolean bottonR_pressed = false;
boolean bottonA_pressed = false;
boolean bottonB_pressed = false;
boolean bottonC_pressed = false;
boolean bottonSD_pressed = false;

uint16_t touchValue;

Adafruit_NeoPixel strip(NEOPIXEL_CNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// use the frame buffer or U8x8 versions for ESP8266, page buffer does not work
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  u8g2.begin();

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)

  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip.show();
  strip.setPixelColor(LEFT_EYE, strip.Color(127, 0, 0));
  strip.setPixelColor(RIGHT_EYE, strip.Color(0, 127, 0));
  strip.show();
}

void loop() {
  read_buttons();

  read_touch();
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_10x20_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  u8g2.drawStr( 0, 0, "@davedarko");
  u8g2.drawStr( 0, 20, "#supercon22");

  u8g2.setFont(u8g2_font_6x10_tf);

  if (bottonU_pressed) u8g2.drawStr(  0, 40, "U");
  if (bottonD_pressed) u8g2.drawStr(  6, 40, "D");
  if (bottonL_pressed) u8g2.drawStr( 12, 40, "L");
  if (bottonR_pressed) u8g2.drawStr( 18, 40, "R");
  if (bottonA_pressed) u8g2.drawStr( 24, 40, "A"); 
  if (bottonB_pressed) u8g2.drawStr( 30, 40, "B");

  // these values need some tweaking
  if (touchValue>90) u8g2.drawStr( 60, 40, "Horn");
  else if (touchValue>60) u8g2.drawStr( 36, 40, "Beak");

  char cstr[16];
  itoa(touchValue, cstr, 10);
  u8g2.drawStr( 84, 40, cstr);

  Serial.print("Horn: ");
  Serial.print(touchValue);
  Serial.println();

  u8g2.sendBuffer();
  delay(100);

  // put your main code here, to run repeatedly:
  //  strip.setPixelColor(LEFT_EYE, strip.Color(127, 0, 0));
  //  strip.setPixelColor(RIGHT_EYE, strip.Color(0, 127, 0));
  //  strip.show();
}

void read_buttons()
{
  Wire.requestFrom(0x38, 1);
  byte data = Wire.read();
  bottonU_pressed = (~data & BUTTON_UP) > 0;
  bottonD_pressed = (~data & BUTTON_DOWN) > 0;
  bottonL_pressed = (~data & BUTTON_LEFT) > 0;
  bottonR_pressed = (~data & BUTTON_RIGHT) > 0;
  bottonA_pressed = (~data & BUTTON_A) > 0;
  bottonB_pressed = (~data & BUTTON_B) > 0;
  bottonC_pressed = (~data & BUTTON_C) > 0;
  bottonSD_pressed = (~data & BUTTON_SD) > 0;
}

void read_touch() {
  Wire.requestFrom(0x11, 1);
  byte b = Wire.read();
  touchValue =  (touchValue + (uint16_t) b)/2;
}
