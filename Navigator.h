#ifndef NAVIGATOR
#define NAVIGATOR

#include <stddef.h>

#include "Controller.h"

class Navigator {
  //TODO: use an abstract interface instead of Controller *
  Controller *controllers[2];
  Controller *controllerStack[4];
  size_t controllerPtr;

  public:
    Navigator();
    void setController(size_t, Controller *);
    Controller *getController(size_t);
    Controller *currentController();
    void replaceController(size_t);
};

#endif
