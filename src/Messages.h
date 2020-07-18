#ifndef MESSAGES
#define MESSAGES 5

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"
#include "Services.h"

class Messages : public Controller {
    public:
        using Controller::Controller;

        Messages(Services *, Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
        /**
         * TODO: replace this with constructor
         */
        void setServices(Services *);
        void begin();
        void handleKeyInput(KeyState state, KeypadEvent key);
        void update();

    private:
        Services *services;
        int8_t numMessages;
        uint8_t curMessage;

        void draw();
        void cursorDown();
        void cursorUp();
};

#endif
