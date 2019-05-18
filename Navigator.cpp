#include "Navigator.h"

Navigator::Navigator()
: controllerPtr(0)
{
}

void Navigator::setController(uint8_t symbol, Controller *controller) {
  controllers[symbol] = controller;
}

Controller *Navigator::getController(uint8_t symbol) {
  return controllers[symbol];
}

Controller *Navigator::currentController() {
  return controllerStack[controllerPtr];
}

void Navigator::popController() {
  Controller *controller = controllerStack[--controllerPtr];
  controller->begin();
}

void Navigator::pushController(uint8_t symbol) {
  Controller *controller = controllers[symbol];
  controller->begin();
  controllerStack[++controllerPtr] = controller;
}

void Navigator::replaceController(uint8_t symbol) {
  Controller *controller = controllers[symbol];
  controller->begin();
  controllerStack[controllerPtr] = controller;
}
