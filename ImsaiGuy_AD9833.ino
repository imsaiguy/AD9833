/*
ImsaiGuy 2023
Program to control AD9833
*/

#include <SPI.h>
#include <U8g2lib.h>
#include <MD_AD9833.h>

#define DATA  6	   ///< SPI Data pin number
#define CLK   7	   ///< SPI Clock pin number
#define FSYNC 5	   ///< SPI Load pin number (FNC on AD9833 breakout)
#define SW1   2	   ///< switch #1
#define SW2   3	   ///< switch #2

long frequency;

MD_AD9833	AD(DATA, CLK, FSYNC); // Arbitrary SPI pins
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, A5,A4, U8X8_PIN_NONE);

void setup()
{
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  AD.begin();
  
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_medsans_tr);
  u8g2.drawStr(0,10,"ImsaiGuy");
  u8g2.drawStr(0,25,"AD9833 Demo");
  u8g2.sendBuffer();
  frequency=1000;
}

void loop()
{
  static uint8_t m = 0;
  static MD_AD9833::mode_t modes[] =
  {
    MD_AD9833::MODE_TRIANGLE,
    MD_AD9833::MODE_SQUARE2,
    MD_AD9833::MODE_SINE,
    MD_AD9833::MODE_SQUARE1
  };
  char ModeName[4][20] = {
  "Triangle",
  "Square",
  "Sine",
  "Square"
};

if (digitalRead(SW1)==0)  {
    m++;                                //next mode
    if (m >= 4) m = 0;                  //too big, back to zero
    AD.setMode(modes[m]);               //set mode
    u8g2.clearBuffer();
    u8g2.drawStr(0,10,"ImsaiGuy");      //display line 1
    u8g2.drawStr(0,25,ModeName[m]);     //display line 2
    u8g2.sendBuffer();
    delay(270);                         //debounce  
  }

if (digitalRead(SW2)==0)  {             
    frequency=frequency*1.1;            //increment 10%
    if (frequency>1000000) frequency=1000;
    AD.setFrequency(MD_AD9833::CHAN_0, frequency);
    delay(100);
  }
}