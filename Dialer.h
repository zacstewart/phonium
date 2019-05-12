#ifndef DIALER
#define DIALER 0

#include "Adafruit_EPD.h"
#include <Keypad.h>

class Dialer {
#include "Common.h"
  Adafruit_SSD1608 *display;
  Keypad *keypad;
  char lastKey;
  char number[NUMBER_LENGTH];
  size_t cur;
  
  public:
    Dialer(Adafruit_SSD1608 *, Keypad *);
    void begin();
    void update();

  private:
    void backspace();
    void callNumber();
};

#endif
