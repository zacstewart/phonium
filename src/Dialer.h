#ifndef DIALER
#define DIALER 1

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class Dialer : public Controller {
  using Controller::Controller;

  char lastKey;
  char number[NUMBER_LENGTH + 1];
  uint8_t cur;

  public:
    Dialer(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
    void begin();
    void handleKeyInput(KeyState state, KeypadEvent key);
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
