#include <Arduino.h>

#include "Waveshare_EPD.h"
#include "Waveshare_GFX.h"

Waveshare_EPD epd = Waveshare_EPD(200, 200);
Waveshare_GFX gfx = Waveshare_GFX(&epd, 200, 200);

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

    Serial.println("Writing Hello epd");

    gfx.fillRect(50, 50, 100, 100, EPD_BLACK);
    gfx.writeMemory();

    gfx.fillRect(25, 25, 100, 100, EPD_WHITE);
    gfx.writeMemory();

    gfx.setCursor(50, 50);
    gfx.setTextColor(EPD_BLACK);
    gfx.print("Hello EPD");
    gfx.writeMemory();

    epd.display();

    Serial.println("Sleeping");
    epd.sleep();

    Serial.println("Done.");
    while (1) { }
#endif
}
