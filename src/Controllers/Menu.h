#ifndef MENU
#define MENU 7

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

namespace Controllers {
    class Menu : public Controller {
        public:
            using Controller::Controller;

            void begin();
            void handleKeyInput(KeyState state, KeypadEvent key);
            void update();
    };
}

#endif
