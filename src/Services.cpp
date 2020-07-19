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

// Adafruit_SharpMem is Adafruit_GFX but that won't necessarily be true if we
// switch to another display device
Adafruit_GFX &Services::getCanvas() {
    return display;
}

Adafruit_SharpMem &Services::getDisplay() {
    return display;
}

Messaging &Services::getMessaging() {
    return messaging;
}
