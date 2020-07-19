#ifndef MESSAGES
#define MESSAGES 5

#include <Adafruit_FONA.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"
#include "Services.h"

class Messages : public Controller {
    public:
        using Controller::Controller;

        Messages(Services &, Navigator *, Keypad *, Adafruit_FONA *);
        void begin();
        void handleKeyInput(KeyState state, KeypadEvent key);
        void update();

    private:
        int8_t numMessages;
        uint8_t curMessage;

        void draw();
        void cursorDown();
        void cursorUp();
};

#endif
