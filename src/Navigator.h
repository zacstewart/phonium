#ifndef NAVIGATOR
#define NAVIGATOR

#include <stdint.h>

#include "Controller.h"

class Navigator {
  //TODO: use an abstract interface instead of Controller *
  Controller *controllers[4];
  Controller *controllerStack[4];
  uint8_t controllerPtr;

  public:
    Navigator();
    void setController(uint8_t, Controller *);
    Controller *getController(uint8_t);
    Controller *currentController();
    void popController();
    void pushController(uint8_t);
    void replaceController(uint8_t);
};

#endif
