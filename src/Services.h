#ifndef SERVICES
#define SERVICES

#include <Adafruit_SharpMem.h>

#include "Messaging.h"

class Services {
    public:
        Services(Adafruit_SharpMem &, Messaging &);

        Adafruit_SharpMem &getDisplay();
        Messaging &getMessaging();

    private:
        Adafruit_SharpMem &display;
        Messaging &messaging;
};

#endif
