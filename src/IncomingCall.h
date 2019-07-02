#ifndef INCOMING_CALL
#define INCOMING_CALL 3

#include <Adafruit_SharpMem.h>
#include <Keypad.h>
#include <Adafruit_FONA.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class IncomingCall : public Controller {
  Navigator *navigator;
  Adafruit_SharpMem *display;
  Keypad *keypad;
  Adafruit_FONA *fona;

  public:
    char number[NUMBER_LENGTH];
    IncomingCall(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
    void begin();
    void update();
    void answerCall();
    void hangUp();
};

#endif
