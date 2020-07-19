#include <Adafruit_SharpMem.h>

#include "Controller.h"

Controller::Controller(Services &services, Navigator &navigator):
    services(services),
    navigator(navigator)
{
}

void Controller::setLeftNavigationLabel(const char *label) {
    Adafruit_GFX &canvas = services.getCanvas();
    canvas.setTextSize(1);
    canvas.setCursor(1, DISPLAY_HEIGHT - 9);
    canvas.print(label);
}

void Controller::setRightNavigationLabel(const char *label) {
    Adafruit_GFX &canvas = services.getCanvas();
    canvas.setTextSize(1);
    canvas.setCursor(
        DISPLAY_WIDTH - (6 * strlen(label)) - 1,
        DISPLAY_HEIGHT - 9
    );
    canvas.print(label);
}
