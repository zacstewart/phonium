#ifndef MESSAGE
#define MESSAGE 6

#include <Adafruit_FONA.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

#include "Messaging.h"

namespace Controllers {
    class Message : public Controller {
        public:
            using Controller::Controller;

            Message(Services &, Navigator &);
            void begin();
            void handleKeyInput(KeyState state, KeypadEvent key);
            void update();

            void setMessage(uint8_t);

        private:
            SmsMessage message;
    };
}

#endif
