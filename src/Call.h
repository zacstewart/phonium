#ifndef CALL
#define CALL 1

#include "Adafruit_EPD.h"
#include <Adafruit_FONA.h>
#include <Keypad.h>

#include "Common.h"
#include "Controller.h"
#include "Dialer.h"

/**
 * This controller is for ongoing calls, incoming or outgoing.
 */
class Call : public Controller {
  Navigator *navigator;
  Adafruit_SSD1608 *display;
  Keypad *keypad;
  Adafruit_FONA *fona;
  char lastKey;
  char number[NUMBER_LENGTH];
  unsigned long callStart;

  public:
    Call(Navigator *, Adafruit_SSD1608 *, Keypad *, Adafruit_FONA *);
    void begin();
    void update();

    Call *setNumber(char *);
    Call *answerCall();
    Call *initiateCall();
    void hangUp();

  private:
    void callEnded();
};

#endif
