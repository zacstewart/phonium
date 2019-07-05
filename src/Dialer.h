#ifndef DIALER
#define DIALER 1

#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class Dialer : public Controller {
  Navigator *navigator;
  Adafruit_SharpMem *display;
  Keypad *keypad;
  char lastKey;
  char number[NUMBER_LENGTH + 1];
  uint8_t cur;

  public:
    Dialer(Navigator *, Adafruit_SharpMem *, Keypad *);
    void begin();
    void update();

    void setNumber(char *);

  private:
    void backspace();
    void callNumber();
    void draw();
    void reset();
    void textNumber();
};

#endif
