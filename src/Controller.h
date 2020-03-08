#ifndef CONTROLLER
#define CONTROLLER

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

// Forward declaration
class Navigator;

class Controller {
  protected:
      Navigator *navigator;
      Adafruit_SharpMem *display;
      Keypad *keypad;
      Adafruit_FONA *fona;

  public:
    Controller(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);

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
