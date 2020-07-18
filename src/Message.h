#ifndef MESSAGE
#define MESSAGE 6

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

#include "Messaging.h"

class Message : public Controller {
    public:
        using Controller::Controller;

        Message(Services *, Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
        void begin();
        void handleKeyInput(KeyState state, KeypadEvent key);
        void update();

        void setMessage(uint8_t);

    private:
        SmsMessage message;
};

#endif
