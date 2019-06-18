#ifndef NAVIGATOR
#define NAVIGATOR

#include <stdint.h>

#include "Controller.h"

class Navigator {
  /**
   * A collection of all controller singleton instances indexed by
   * their magic number constant
   */
  Controller *controllers[6];
  /**
   * A stack of controllers that have been pushController-ed.
   * Should be as small as possible but still account for the max
   * navigational depth.
   *
   * TODO: static-analyze max controller depth
   */
  Controller *controllerStack[4];
  /**
   * A pointer to index into controllers for the top of th stack.
   */
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
