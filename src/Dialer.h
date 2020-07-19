#ifndef DIALER
#define DIALER 1

#include <Adafruit_FONA.h>

#include "Common.h"
#include "Controller.h"
#include "Navigator.h"

class Dialer : public Controller {
    public:
        using Controller::Controller;

        Dialer(Services &, Navigator *, Adafruit_FONA *);
        void begin();
        void handleKeyInput(KeyState state, KeypadEvent key);
        void update();

        void setNumber(char *);

    private:
        char lastKey;
        char number[NUMBER_LENGTH + 1];
        uint8_t cur;

        void backspace();
        void callNumber();
        void draw();
        void reset();
        void textNumber();
};

#endif
