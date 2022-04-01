/*

  MCU                       Any compatible with TFT_eSPI
  Display                   Any compatible with TFT_eSPI
  display library           https://github.com/Bodmer/TFT_eSPI
  extension library         https://github.com/Bodmer/TFT_eSPI_ext

  BarChartH(TFT_eSPI *disp, float GraphXLoc, float GraphYLoc, float GraphWidth, float GraphHeight, float ScaleLow, float ScaleHigh, float ScaleInc);
  void init(const char *Title, uint16_t TextColor, uint16_t BarColor, uint16_t BarBColor, uint16_t BackColor,const ILI9341_t3_font_t &TitleFont , const ILI9341_t3_font_t &ScaleFont );
  void setBarColor(uint16_t val = 0xF800);
  void plot(float val);
  void setScale(float ScaleLow, float ScaleHigh, float ScaleInc);
  void showTitle(bool val);
  void showScale(bool val);

*/


/*

  To implement a button is 4 lines of code, look for the Step x below

*/
#include <TFT_eSPI.h>
#include <TFT_eSPI_ext.h> 

// step 1 include the library
#include <ILI9341_t3_Controls.h>
#include <font_Arial.h>

#define FONT_TITLE Arial_24
#define FONT_DATA Arial_10

#define B_XORIGIN 70
#define B_YORIGIN 70
#define B_WIDE 170
#define B_HEIGHT 20
#define B_LOWSCALE 0
#define B_HIGHSCALE 4.0
#define B_SCALEINC 1.0


#define V_XORIGIN 50
#define V_YORIGIN 150
#define V_WIDE 200
#define V_HEIGHT 50
#define V_LOWSCALE 0
#define V_HIGHSCALE 4.0
#define V_SCALEINC .5

#define BORDERCOLOR C_WHITE
#define BACKCOLOR C_BLACK

TFT_eSPI      tft = TFT_eSPI();
TFT_eSPI_ext  Display = TFT_eSPI_ext(&tft);

int a7Bits, a8Bits;
float a7Volts, a8Volts;

// step 2 create an object for each bar chart
BarChartH A7Volts(&Display );
BarChartH A8Volts(&Display );

void setup() {
  Serial.begin(115200);

  Display.begin();
  Display.setRotation(1);
  Display.fillScreen(TFT_BLACK);
//  digitalWrite(LED_PIN, HIGH);

  // step 3 initialize
  //while(1) delay(100);
  A7Volts.init(B_XORIGIN, B_YORIGIN, B_WIDE, B_HEIGHT, B_LOWSCALE, B_HIGHSCALE, B_SCALEINC, "A7 Voltage", C_WHITE, BORDERCOLOR, C_RED, C_DKRED, BACKCOLOR, FONT_TITLE, FONT_DATA);
  // these methods are optional but let you see what you can do
  // A7Volts.ShowScale(false);
  // A7Volts.ShowTitle(false);
  // A7Volts.Plot(0);

  A8Volts.init(V_XORIGIN, V_YORIGIN, V_WIDE, V_HEIGHT, V_LOWSCALE, V_HIGHSCALE, V_SCALEINC, "A8 Voltage", C_WHITE, BACKCOLOR, C_BLUE, C_DKBLUE, BACKCOLOR, FONT_TITLE, FONT_DATA);
  // these methods are optional but let you see what you can do
  A8Volts.showScale(false);
  // A8Volts.showTitle(false);
  // A8Volts.plot(0);

}

void loop() {

  a7Bits = random(1024);
  a8Bits = random(1024);

  a7Volts = a7Bits * 3.3 / 1024;
  a8Volts = a8Bits * 3.3 / 1024;

  // step 4 draw
  A7Volts.draw(a7Volts);
  A8Volts.draw(a8Volts);
  delay(50);

}
