#include <Arduino.h>

#include "Waveshare_EPD.h"

Waveshare_EPD epd;

extern "C" int main(void) {
#ifdef USING_MAKEFILE
#ifdef DEBUG
    while (!Serial);
#endif

    Serial.begin(115200);

#ifdef DEBUG
    Serial.print("Build date: ");
    Serial.println(BUILD_DATE);
#endif
    Serial.println("Initializing");
    epd.begin();

    Serial.println("Clearing");
    epd.clear();

    Serial.println("Sleeping");
    epd.sleep();

    Serial.println("Trying to clear after waking");
    epd.wake();
    epd.clear();

    Serial.println("Sleeping");
    epd.sleep();

    Serial.println("Done.");
    while (1) { }
#endif
}
