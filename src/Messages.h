#ifndef MESSAGES
#define MESSAGES 5

#include <Adafruit_EPD.h>
#include <Adafruit_FONA.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class Messages : public Controller {
  Navigator *navigator;
  Adafruit_SSD1608 *display;
  Keypad *keypad;
  Adafruit_FONA *fona;

  public:
    Messages(Navigator *, Adafruit_SSD1608 *, Keypad *, Adafruit_FONA *);
    void begin();
    void update();
};

#endif
