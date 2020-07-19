#include <Adafruit_SharpMem.h>

#include "Controller.h"

Controller::Controller(Services &services, Navigator *navigator, Keypad *keypad, Adafruit_FONA *fona):
    services(services),
    navigator(navigator),
    keypad(keypad),
    fona(fona)
{
}

void Controller::setLeftNavigationLabel(const char *label) {
    Adafruit_SharpMem &display = services.getDisplay();
    display.setTextSize(1);
    display.setCursor(1, DISPLAY_HEIGHT - 9);
    display.print(label);
}

void Controller::setRightNavigationLabel(const char *label) {
    Adafruit_SharpMem &display = services.getDisplay();
    display.setTextSize(1);
    display.setCursor(
        DISPLAY_WIDTH - (6 * strlen(label)) - 1,
        DISPLAY_HEIGHT - 9
    );
    display.print(label);
}
