#include "Navigator.h"

Navigator::Navigator()
: controllerPtr(0)
{
}

void Navigator::setController(size_t symbol, Controller *controller) {
  controllers[symbol] = controller;
}

Controller *Navigator::getController(size_t symbol) {
  return controllers[symbol];
}

Controller *Navigator::currentController() {
  return controllerStack[controllerPtr];
}

void Navigator::replaceController(size_t symbol) {
  Controller *controller = controllers[symbol];
  controller->begin();
  controllerStack[controllerPtr] = controller;
}