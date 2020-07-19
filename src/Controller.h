#ifndef CONTROLLER
#define CONTROLLER

#include <Adafruit_FONA.h>
#include <Keypad.h>

#include "Common.h"
#include "Services.h"

// Forward declaration
class Navigator;

class Controller {
    protected:
        Services &services;
        Navigator &navigator;

        void setLeftNavigationLabel(const char *);
        void setRightNavigationLabel(const char *);

    public:
        Controller(Services &, Navigator &);

        /**
         * When this controller takes control
         */
        virtual void begin() = 0;

        /**
         * Called every tick of main loop when in control
         */
        virtual void update() = 0;

        /**
         * Called for every Keypad event
         */
        virtual void handleKeyInput(KeyState, KeypadEvent) = 0;
};

#endif
