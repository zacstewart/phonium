#ifndef HOME
#define HOME 0

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class Home : public Controller {
  using Controller::Controller;

  public:
    void begin();
    void handleKeyInput(KeyState state, KeypadEvent key);
    void update();

  private:
    void startDialing(char);
};

#endif
