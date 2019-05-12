#include "Adafruit_EPD.h"
#include <Keypad.h>

class Dialer {
  Adafruit_SSD1608 *display;
  Keypad *keypad;
  char number[30];
  char lastKey;
  size_t cur;
  
  public:
    Dialer(Adafruit_SSD1608 *, Keypad *);
    void begin();
    void update();
  private:
    void backspace();
    void callNumber();
};
