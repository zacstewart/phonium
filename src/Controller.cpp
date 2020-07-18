#include "Controller.h"

Controller::Controller(Services *services, Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona):
    services(services),
    navigator(navigator),
    display(display),
    keypad(keypad),
    fona(fona)
{
}

void Controller::setLeftNavigationLabel(char *label) {
    display->setTextSize(1);
    display->setCursor(1, DISPLAY_HEIGHT - 9);
    display->print(label);
}

void Controller::setRightNavigationLabel(char *label) {
    display->setTextSize(1);
    display->setCursor(
        DISPLAY_WIDTH - (6 * strlen(label)) - 1,
        DISPLAY_HEIGHT - 9
    );
    display->print(label);
}
