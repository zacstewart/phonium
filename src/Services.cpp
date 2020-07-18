#include "Services.h"

Services::Services(Adafruit_SharpMem display, Messaging messaging):
    messaging(messaging)
{
}

Messaging *Services::getMessaging() {
    return &messaging;
}
