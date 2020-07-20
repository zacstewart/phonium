#ifndef HOME
#define HOME 0

#include "Common.h"
#include "Controller.h"

namespace Controllers {
    class Home : public Controller {
        public:
            using Controller::Controller;

            void begin();
            void handleKeyInput(KeyState state, KeypadEvent key);
            void update();

        private:
            void startDialing(char);
    };
}

#endif
