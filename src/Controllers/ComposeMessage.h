#ifndef COMPOSE_MESSAGE
#define COMPOSE_MESSAGE 4

#include <Adafruit_FONA.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

namespace Controllers {
    class ComposeMessage : public Controller {
        public:
            using Controller::Controller;

            ComposeMessage(Services &, Navigator &);
            void begin();
            void handleKeyInput(KeyState state, KeypadEvent key);
            void update();

            void setNumber(char *);

        private:
            char lastKey;
            uint8_t lastCharSet;
            unsigned long lastInputAt;
            uint8_t curChar;
            char number[NUMBER_LENGTH + 1];
            char message[MESSAGE_LENGTH + 1];
            uint8_t cur;

            void backspace();
            void draw();
            void handleTextEntry(uint8_t);
            void reset();
            void sendMessage();
    };
}

#endif
