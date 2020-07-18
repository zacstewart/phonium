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
    public:
        using Controller::Controller;

        Call(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
        void begin();
        void handleKeyInput(KeyState state, KeypadEvent key);
        void update();

        Call *setNumber(char *);
        Call *answerCall();
        Call *initiateCall();
        void hangUp();

    private:
        char lastKey;
        char number[NUMBER_LENGTH + 1];
        unsigned long callStart;

        void callEnded();
};

#endif
