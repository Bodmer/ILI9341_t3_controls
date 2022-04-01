/*

  MCU                       Any compatible with TFT_eSPI
  Display                   Any compatible with TFT_eSPI
  display library           https://github.com/Bodmer/TFT_eSPI
  extension library         https://github.com/Bodmer/TFT_eSPI_ext


  BarChartV(TFT_eSPI *disp, float GraphXLoc, float GraphYLoc, float GraphWidth, float GraphHeight, float ScaleLow, float ScaleHigh, float ScaleInc);
  void init(const char *Title, uint16_t TextColor, uint16_t BarColor, uint16_t BarBColor, uint16_t BackColor,const ILI9341_t3_font_t &TitleFont , const ILI9341_t3_font_t &ScaleFont );
  void setBarColor(uint16_t val = 0xF800);
  void draw(float val);
  void setScale(float ScaleLow, float ScaleHigh, float ScaleInc);
  void showTitle(bool val);
  void showScale(bool val);

*/

/*

  implementation is 4 lines of code, see step xxx below

*/

#include <TFT_eSPI.h>
#include <TFT_eSPI_ext.h> 

// step 1 implement the library
#include <ILI9341_t3_Controls.h>

#include <font_Arial.h>  // custom control define file

#define FONT_TITLE Arial_24
#define FONT_DATA Arial_16

#define LED_PIN       LED_BUILTIN

TFT_eSPI      tft = TFT_eSPI();
TFT_eSPI_ext  Display = TFT_eSPI_ext(&tft);

int a7Bits, a8Bits;
float a7Volts, a8Volts;

// step 2 create the bar chart objects
BarChartV A7Volts(&Display );
BarChartV A8Volts(&Display );

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  Display.begin();
  Display.setRotation(1);
  Display.fillScreen(TFT_BLACK);
  digitalWrite(LED_PIN, HIGH);

  // step 3 initialize the bar chart objects
  A7Volts.init(   0, 230, 50, 180, 0, 4.0, 1.0, "A7", C_WHITE, C_WHITE, C_RED, C_BLACK, C_BLACK, FONT_TITLE, FONT_DATA);
  A8Volts.init(120,  230, 50, 180, 0, 4.0, 0.5, "A8", C_WHITE, C_BLACK, C_GREEN, C_DKGREEN,  C_BLACK, FONT_TITLE, FONT_DATA);

  // optional but shows how you can hide the scale
  A8Volts.showScale(false);
}

void loop() {

  a7Bits = random(1024);
  a8Bits = random(1024);

  a7Volts = a7Bits * 3.3 / 1024;
  a8Volts = a8Bits * 3.3 / 1024;

  // optional but shows how to change the color after init
  if (a7Volts > 2) {
    A7Volts.setBarColor(C_RED);
  }
  else {
    A7Volts.setBarColor(C_BLUE);
  }

  if (a8Volts > 2) {
    A8Volts.setBarColor(C_RED);
  }
  else {
    A8Volts.setBarColor(C_GREEN);
  }

  // step 4 draw the bar chart objects
  A7Volts.draw(a7Volts);
  A8Volts.draw(a8Volts);

  delay(50);


}
