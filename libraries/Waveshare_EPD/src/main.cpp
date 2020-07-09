#include <Arduino.h>

#include "Waveshare_EPD.h"

Waveshare_EPD epd = Waveshare_EPD(200, 200);

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

    Serial.println("Writing Hello epd");

    epd.fillRect(50, 50, 100, 100, EPD_WHITE);
    epd.writeMemory();
    epd.display();

    epd.fillRect(25, 25, 100, 100, EPD_BLACK);
    epd.writeMemory();
    epd.display();

    epd.setCursor(50, 50);
    epd.setTextColor(EPD_WHITE);
    epd.print("Hello EPD");
    epd.writeMemory();
    epd.display();

    Serial.println("Sleeping");
    epd.sleep();

    Serial.println("Done.");
    while (1) { }
#endif
}
