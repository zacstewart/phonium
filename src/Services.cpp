#include "Services.h"

Services::Services(Adafruit_FONA &fona, Adafruit_SharpMem &display, Messaging &messaging):
    fona(fona),
    display(display),
    messaging(messaging)
{
}

Adafruit_FONA &Services::getFona() {
    return fona;
}

Adafruit_SharpMem &Services::getDisplay() {
    return display;
}

Messaging &Services::getMessaging() {
    return messaging;
}
