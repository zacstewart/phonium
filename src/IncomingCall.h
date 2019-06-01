#ifndef INCOMING_CALL
#define INCOMING_CALL 2

#include "Adafruit_EPD.h"
#include <Keypad.h>
#include <Adafruit_FONA.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class IncomingCall : public Controller {
  Navigator *navigator;
  Adafruit_SSD1608 *display;
  Keypad *keypad;
  Adafruit_FONA *fona;

  public:
    char number[NUMBER_LENGTH];
    IncomingCall(Navigator *, Adafruit_SSD1608 *, Keypad *, Adafruit_FONA *);
    void begin();
    void update();
    void answerCall();
    void hangUp();
};

#endif
