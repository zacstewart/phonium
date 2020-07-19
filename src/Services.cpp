#include "Services.h"

Services::Services(Adafruit_SharpMem &display, Messaging &messaging):
    display(display),
    messaging(messaging)
{
}

Adafruit_SharpMem &Services::getDisplay() {
    return display;
}

Messaging &Services::getMessaging() {
    return messaging;
}
