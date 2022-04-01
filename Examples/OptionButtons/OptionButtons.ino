/*

  MCU                       Any compatible with TFT_eSPI
  Display                   Any compatible with TFT_eSPI
  display library           https://github.com/Bodmer/TFT_eSPI
  extension library         https://github.com/Bodmer/TFT_eSPI_ext

  // required
  OptionButton(TFT_eSPI *Display) {d = Display; }
  void init(uint16_t OutlineColor, uint16_t SelectedColor, uint16_t UnSelectedColor, int16_t TextColor, uint16_t BackgroundColor, int TextOffsetX,int TextOffsetY, const ILI9341_t3_font_t &TextFont) {
  int add(uint16_t ButtonX, uint16_t ButtonY,const char *Text ) {
  void draw(int OptionID) {
  int press(uint16_t ScreenX, uint16_t ScreenY) // returns if control was clicked. use value property to get the selected option

  // optional button methods
  void select(int val) {
  void show() {
  void hide() {
  void disable() {
  void enable() {
  void resize(byte radius) {
  void setColors(uint16_t OutlineColor, uint16_t SelectedColor, uint16_t UnSelectedColor, uint16_t TextColor, uint16_t BackgroundColor, uint16_t DisableOutlineColor, uint16_t DisableSelColor, uint16_t DisableUnSelColor, uint16_t DisableTextColor) {
  void setFont(int TextOffsetX,int TextOffsetY, const ILI9341_t3_font_t &TextFont) {
  void setText(int ID, const char *Text) {
  int selected() {
  bool isEnable() {
  bool isVisible() {
  void setPressDebounce(byte Debounce) {
  int value;

*/

/*

  To implement an option button group is 6 lines of code, look for the Step x below

*/

#include <TFT_eSPI.h>
#include <TFT_eSPI_ext.h>
// step 1 include the library
#include <ILI9341_t3_Controls.h>  // custom control define file
#include <font_Arial.h>

#define FONT Arial_16

#define BACKCOLOR    C_BLACK
#define ROW1 60
#define ROW2 90
#define ROW3 120
#define ROW4 150
#define ROW5 200

#define COL1 10
#define COL2 180

int OptionA0ID, OptionA1ID, OptionA2ID, OptionA3ID, OptionA4ID;
int OptionB0ID, OptionB1ID, OptionB2ID, OptionB3ID, OptionB4ID;

uint16_t BtnX, BtnY;

// create the display object
TFT_eSPI      tft = TFT_eSPI();
TFT_eSPI_ext  Display = TFT_eSPI_ext(&tft);

// step 2 create an option button GROUP (not individual options), pass in the display object
OptionButton OBA(&Display);
OptionButton OBB(&Display);

CheckBox CB1(&Display);
CheckBox CB2(&Display);

void setup() {

  Serial.begin(9600);

  // step 3 initialize each option button group, passing in colors,
  // button text offsets (to help manage text location on the button and the ILI9341 font
  OBA.init(C_WHITE, C_GREEN, C_DKGREY, C_WHITE, C_BLACK, 20, -2, Arial_14 );

  // step 4 Add an option to be listed in the button group, passing in location,
  // and text
  OptionA0ID = OBA.add(COL1, ROW1, "Apples");
  OptionA1ID = OBA.add(COL1, ROW2, "Oranges");
  OptionA2ID = OBA.add(COL1, ROW3, "Mangos");
  OptionA3ID = OBA.add(COL1, ROW4, "Strawberries");

  OBB.init(C_WHITE, C_GREEN, C_DKGREY, C_WHITE, C_DKGREY, 20, -2, Arial_14 );
  OptionB0ID = OBB.add(COL2, ROW1, "Steak");
  OptionB1ID = OBB.add(COL2, ROW2, "Pork");
  OptionB2ID = OBB.add(COL2, ROW3, "Chicken");
  OptionB3ID = OBB.add(COL2, ROW4, "Fish");

  CB1.init(COL1, ROW5, C_WHITE, C_GREEN, C_DKGREY, C_WHITE, C_BLACK, 30, 2, "Enable", Arial_14 );
  CB2.init(COL2, ROW5, C_WHITE, C_GREEN, C_DKGREY, C_WHITE, C_BLACK, 30, 2, "Show", Arial_14 );


  // fire up the display
  Display.begin();

  // fire up the touch display
  uint16_t calData[5] = { 243, 3657, 243, 3576, 7 };
  Display.setTouch(calData);

  Display.invertDisplay(false);
  Display.fillScreen(BACKCOLOR);
  Display.setRotation(1);

  Display.fillRect(0, 0, 480, 50, C_DKBLUE);
  Display.setTextColor(C_WHITE);
  Display.setTTFont(Arial_24);
  Display.setCursor(10 , 10 );
  Display.print(F("Options Example"));


  Display.fillRect(5, 55, 320 / 2 - 10, 240 - 55 - 10, C_DKGREY);
  Display.fillRect(320 / 2 + 10, 55, 320 / 2 - 10, 240 - 55 - 10, C_DKGREY);

  // optional, you can set other parameters before the draw method (color and default selected
  // option for example)
  // step 5 draw each option button group (this method will automatically draw
  // all items in the group

  OBA.draw(0);
  OBB.draw(1);

  CB1.draw(true);
  CB2.draw(true);

}

void loop() {

  if (Display.getTouch(&BtnX, &BtnY)) {
    ProcessTouch();

    // if you really need to monitor if the control was clicked
    // here's how, this may be needed if you have a complicated UI
    // and don't need to automatically change things--code here shows 2 cases
    // 1) automatically updates items based on check box value (see if else sections, these
    // run even of check box was not pressed
    // and 2) only updating items if the check box was changed
    // do not use the return value as check box state
    // only use Checkbox.value for the state
    bool changed = CB1.press(BtnX, BtnY);
    CB2.press(BtnX, BtnY);


    // step 6 proces the option group (this mehod will pass back the selected option
    // so no need to rip through each option to test if selected. this call will pass back
    // the selected option
    OBA.press(BtnX, BtnY);
    OBB.press(BtnX, BtnY);

    // process option A group
    if (OBA.value == OptionA0ID) {
      // your code goes here
    }
    else if (OBA.value == OptionA1ID) {
      // your code goes here
    }
    else if (OBA.value == OptionA2ID) {
      // your code goes here
    }
    else if (OBA.value == OptionA3ID) {
      // your code goes here
    }

    //process option B group
    if (OBB.value == OptionB0ID) {
      // your code goes here
    }
    else if (OBB.value == OptionB1ID) {
      // your code goes here
    }
    else if (OBB.value == OptionB2ID) {
      // your code goes here
    }
    else if (OBB.value == OptionB3ID) {
      // your code goes here
    }

    // as mentioned above, you you don't want to process code unless checkbox was clicked
    // wrap a change test around checkbox values
    if (changed) {
      if (CB1.value) {
        Serial.println("enabling");
        OBA.enable();
        OBA.draw(OBA.value);
      }
      else {
        Serial.println("disabling");
        OBA.disable();
        OBA.draw(OBA.value);
      }
    }

    // as mentioned above, you code processes regardless if checkbox was clicked
    if (CB2.value) {
      Serial.println("showing");
      OBB.show();
      OBB.draw(OBB.value);
    }
    else {
      Serial.println("hiding");
      OBB.hide();
      OBB.draw(OBB.value);
    }


  }


}

// my own processing function to handle press and convert to proper screen
// coordinates
// i've found so many differences between different screens, i needed an easy
// way to handle returning screen calcualtions
// my code uses global button x and button y locations
void ProcessTouch() {


}
