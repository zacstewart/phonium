#include "Services.h"

Services::Services(Adafruit_FONA &fona, Display &display, Messaging &messaging):
    fona(fona),
    display(display),
    messaging(messaging)
{
}

Adafruit_FONA &Services::getFona() {
    return fona;
}

Display &Services::getDisplay() {
    return display;
}

Messaging &Services::getMessaging() {
    return messaging;
}
