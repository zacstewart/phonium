#ifndef SERVICES
#define SERVICES

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>

#include "Messaging.h"

class Services {
    public:
        Services(Adafruit_FONA &, Adafruit_SharpMem &, Messaging &);

        Adafruit_FONA &getFona();
        Adafruit_SharpMem &getDisplay();
        Messaging &getMessaging();

    private:
        Adafruit_FONA &fona;
        Adafruit_SharpMem &display;
        Messaging &messaging;
};

#endif
