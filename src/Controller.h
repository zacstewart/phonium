#ifndef CONTROLLER
#define CONTROLLER

#include <Keypad.h>

class Controller {
  public:
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
