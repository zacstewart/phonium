#ifndef CALL
#define CALL 2

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Controller.h"
#include "Dialer.h"

/**
 * This controller is for ongoing calls, incoming or outgoing.
 */
class Call : public Controller {
  Navigator *navigator;
  Adafruit_SharpMem *display;
  Keypad *keypad;
  Adafruit_FONA *fona;
  char lastKey;
  char number[NUMBER_LENGTH + 1];
  unsigned long callStart;

  public:
    Call(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
    void begin();
    void handleKeyInput(KeyState state, KeypadEvent key);
    void update();

    Call *setNumber(char *);
    Call *answerCall();
    Call *initiateCall();
    void hangUp();

  private:
    void callEnded();
};

#endif
