#ifndef INCOMING_CALL
#define INCOMING_CALL 3

#include <Adafruit_SharpMem.h>
#include <Keypad.h>
#include <Adafruit_FONA.h>

#include "Common.h"
#include "Controller.h"
#include "Navigator.h"

class IncomingCall : public Controller {
    public:
        using Controller::Controller;

        char number[NUMBER_LENGTH + 1];

        IncomingCall(Services *, Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
        void begin();
        void handleKeyInput(KeyState state, KeypadEvent key);
        void update();

        void answerCall();
        void hangUp();
};

#endif
