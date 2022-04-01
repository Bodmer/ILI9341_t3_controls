/*

  MCU                       Any compatible with TFT_eSPI
  Display                   Any compatible with TFT_eSPI
  display library           https://github.com/Bodmer/TFT_eSPI
  extension library         https://github.com/Bodmer/TFT_eSPI_ext

    available methods

    // required
  SliderH(TFT_eSPI *Display);   // class constructor
  void init(uint16_t SliderX, uint16_t SliderY, uint16_t SliderW, float ScaleLow, float ScaleHi, float Scale, float Snap, uint16_t SliderColor, uint16_t BackgroundColor, uint16_t HandleColor);    // initializer
  void draw(float val);         // method to draw complete slider
  float slide(float ScreenX, float ScreenY);       // method to move handle as user drags finger over handle,
  // automatically looks for a valid range press returns if control was clicked. use value property to get the selected option


  // optional
  bool changed();
  void setColors(uint16_t SliderColor, uint16_t BackgroundColor, uint16_t HandleColor);   // way to reset colors (useful for drawing enabled or disabled)
  void setHandleColor(uint16_t HandleColor);  // method to just draw the handle (useful for showing handle in green for OK value
  void setDisableColor(uint16_t HandleColor, uint16_t SliderColor); // method to just draw the handle (useful for showing handle in green for OK value
  void setHandleSize(int size);
  void disable();
  void enable();
  void show();
  void hide();
  void setHandleShape(byte shape);
  void drawSliderColor(bool color);
  void setPressDebounce(byte Debounce);
  float value;

*/


/*

  Implementatin is 5 steps

*/
#include <TFT_eSPI.h>
#include <TFT_eSPI_ext.h>
// step 1 include the lib
#include <ILI9341_t3_Controls.h>  // custom control define file
#include <font_Arial.h>

#define FONT Arial_16

// defines for locations
#define ROW0 30
#define ROW1 70
#define ROW2 110
#define ROW3 150
#define ROW4 190

byte RedByte = 70, GreenByte = 170, BlueByte = 210, BrightByte = 255;
uint16_t BtnX, BtnY;

char buf[22];
uint16_t color, oldcolor;

// create display and DS objects
TFT_eSPI      tft = TFT_eSPI();
TFT_eSPI_ext  Display = TFT_eSPI_ext(&tft);

// step 2 create the objects
//SliderH Red(&Display, left, top, width, bar color, back color, ball color);
SliderH Bright(&Display);
SliderH Red(&Display);
SliderH Green(&Display);
SliderH Blue(&Display);


void setup() {

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // step 3 initialize each slider
  // low limit, high limit, scale val (0 is off), snap value (0 is off))
  Bright.init (20, ROW1, 100, 55, 255,     0, 0, C_WHITE, C_BLACK, C_GREY);

  Red.init    (20, ROW2, 100, 0, 255, 127.5, 0, C_WHITE, C_BLACK, C_RED);
  Green.init  (20, ROW3, 100, 0, 255, 63.75, 0, C_WHITE, C_BLACK, C_GREEN);
  Blue.init   (20, ROW4, 100, 0, 255,     0, 0, C_WHITE, C_BLACK, C_BLUE);

  // fire up the display
  Display.begin();

  // fire up the touch display
  uint16_t calData[5] = { 243, 3657, 243, 3576, 7 };
  Display.setTouch(calData);

  Display.invertDisplay(false);
  Display.fillScreen(C_BLACK);

  // set some display settings
  Display.setRotation(1);
  Display.setTextSize(2);
  Display.setTextColor(C_WHITE, C_BLACK);
  Display.setTTFont(FONT);
  Display.setCursor(10 , 10 );
  Display.print(F("Color Picker"));

  // Step 4 draw each slider
  Red.draw(RedByte);
  Green.draw(GreenByte);
  Blue.draw(BlueByte);
  Bright.draw(BrightByte);

  color = Display.color565(RedByte, GreenByte, BlueByte);

  // draw a color box
  Display.drawRect(140, 80, 100, 100, C_WHITE);
  Display.drawRect(141, 81, 98, 98, C_WHITE);
  Display.fillRect(142, 82, 96, 96, color);

  sprintf(buf, "0x%04X, %3d, %3d, %3d         ", color, RedByte, GreenByte, BlueByte);
  Display.setCursor(50 , 220 );
  Display.print(buf);

}


void loop() {

  // wait for touch
  if (Display.getTouch(&BtnX, &BtnY)) {
    ProcessTouch();

    // how to enable disable a slider
    // example on how to change slider colors

    // Step 5 allow user to slide the control and proces results
    // if you really need to monitor if the control was clicked
    // here's how, this may be needed if you have a complicated UI
    // and don't need to automatically change things--code here shows 2 cases
    // 1) automatically updates items based on slider (see if else sections, these
    // run even if slider was not pressed
    // and 2) only updating items if the slider was changed
    // do not use the return value as slider value
    // only use SliderV.value for the value

    bool changed = Bright.slide(BtnX, BtnY);
    // note if touch is not in range of slider, operation will be ignored
    // meaning you don't need to test press location--the lib does that
    Red.slide(BtnX, BtnY);
    Green.slide(BtnX, BtnY);
    Blue.slide(BtnX, BtnY);

    // update the color swatch
    // as mentioned above, you you don't want to process code unless slider was moved
    // wrap a change test around checkbox values
    // here only the band 1 screen text updates
    if (!changed) {
      color = Display.color565(Red.value, Green.value, Blue.value);
      Display.drawRect(140, 80, 100, 100, C_WHITE);
      Display.drawRect(141, 81, 98, 98, C_WHITE);
      Display.fillRect(142, 82, 96, 96, color);
      Display.fillRect(50, 220, 200, 50, C_BLACK);
      sprintf(buf, "0x%04X, %3d, %3d, %3d  ", color, (int)Red.value, (int) Green.value, (int) Blue.value);
      Display.setCursor(50 , 220 );
      Display.print(buf);
    }
    // as mentioned above, you code processes regardless if slider was moved
    // here we reset brightness on ANY slider move--don't like it? add changed check to
    // only process if bright slider was moved
    analogWrite(LED_BUILTIN, Bright.value);
  }

}

void ProcessTouch() {

  //Serial.print(", Mapped coordinates: ");
  //Serial.print(BtnX);
  //Serial.print(",");
  //Serial.println(BtnY);
  //Display.drawPixel(BtnX, BtnY, C_GREEN);

}
