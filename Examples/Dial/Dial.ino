#include <TFT_eSPI.h>
#include <TFT_eSPI_ext.h>
#include <ILI9341_t3_Controls.h>
#include <font_Arial.h>
#include <font_ArialBold.h>
#define FONT_TITLE Arial_16
#define FONT_DATA Arial_10_Bold

// defines for locations
#define BXCENTER 80
#define BYCENTER 120
#define BDIAMETER 75
#define BLOWSCALE 0
#define BHIGHSCALE 1200
#define BSCALEINC 200
#define BSWEEPANGLE 300

#define VXCENTER 240
#define VYCENTER 120
#define VDIAMETER 75
#define VLOWSCALE 0
#define VHIGHSCALE 4
#define VSCALEINC .5
#define VSWEEPANGLE 300

// defines for colors
#define BNEEDLECOLOR C_ORANGE
#define BDIALCOLOR C_DKBLUE
#define BTEXTCOLOR C_WHITE
#define BTICCOLOR C_GREY

#define VNEEDLECOLOR C_WHITE
#define VDIALCOLOR C_DKBLUE
#define VTEXTCOLOR C_WHITE
#define VTICCOLOR C_GREY

// create the display object
TFT_eSPI      tft = TFT_eSPI();
TFT_eSPI_ext  Display = TFT_eSPI_ext(&tft);

int bBits;
float bVolts;
float bData;

// create the dial object(s)
Dial Bits(&Display, BXCENTER, BYCENTER, BDIAMETER, BLOWSCALE , BHIGHSCALE, BSCALEINC, BSWEEPANGLE);
Dial Volts(&Display, VXCENTER, VYCENTER, VDIAMETER, VLOWSCALE , VHIGHSCALE, VSCALEINC, VSWEEPANGLE);

void setup() {
  Serial.begin(115200);

  Display.begin();
  Display.setRotation(1);
  Display.fillScreen(C_BLACK);

  // initialize the dials
  Bits.init(BNEEDLECOLOR, BDIALCOLOR, BTEXTCOLOR, BTICCOLOR, "Bits", FONT_TITLE, FONT_DATA);
  Volts.init(VNEEDLECOLOR, VDIALCOLOR, VTEXTCOLOR, VTICCOLOR, "Volts", FONT_TITLE, FONT_DATA);

}

void loop() {
  static float x = 0;
  // get some data
  bBits = (1.0 + sin(x)) * 1024/2;
  bVolts = bBits * 3.3 / 1024;

  // update the dials
  Bits.draw(bBits);
  Volts.draw(bVolts);

  // bump the x value
  x += .1;
  delay(150);


}
