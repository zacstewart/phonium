#ifndef DIALER
#define DIALER 0

#include "Adafruit_EPD.h"
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class Dialer : public Controller {
  Navigator *navigator;
  Adafruit_SSD1608 *display;
  Keypad *keypad;
  char lastKey;
  char number[NUMBER_LENGTH];
  size_t cur;
  
  public:
    Dialer(Navigator *, Adafruit_SSD1608 *, Keypad *);
    void begin();
    void update();

  private:
    void backspace();
    void callNumber();
};

#endif
