#include "Controller.h"

Controller::Controller(Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona)
: navigator(navigator)
, display(display)
, keypad(keypad)
, fona(fona)
{
}
