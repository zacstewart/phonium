#ifndef MENU
#define MENU 7

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class Menu : public Controller {
  using Controller::Controller;

  public:
    void begin();
    void handleKeyInput(KeyState state, KeypadEvent key);
    void update();
};

#endif
