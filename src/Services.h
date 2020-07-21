#ifndef SERVICES
#define SERVICES

#include <Adafruit_FONA.h>
#include <Adafruit_GFX.h>

#include "Display.h"
#include "Messaging.h"

class Services {
    public:
        Services(Adafruit_FONA &, Display &, Messaging &);

        Adafruit_FONA &getFona();
        /**
         * Returns an Adafruit_GFX object that can be used to draw UI elements
         * in memory. The display object from getDisplay will need to be
         * invoked in order to transfer the canvas image into the display
         * device and render it.
         */
        Display &getDisplay();
        Messaging &getMessaging();

    private:
        Adafruit_FONA &fona;
        Display &display;
        Messaging &messaging;
};

#endif
