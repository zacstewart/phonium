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

    gfx.fillRect(65, 65, 100, 100, EPD_BLACK);
    gfx.writeMemory();

    gfx.fillRect(40, 40, 100, 100, EPD_WHITE);
    gfx.writeMemory();

    gfx.fillRect(35, 35, 100, 100, EPD_BLACK);
    gfx.writeMemory();

    gfx.setCursor(50, 50);
    gfx.setTextColor(EPD_WHITE);
    gfx.print("Hello EPD");
    gfx.writeMemory();

    epd.display();

    gfx.fillRect(0, 0, 5, 5, EPD_BLACK);
    gfx.fillRect(195, 0, 5, 5, EPD_BLACK);
    gfx.fillRect(195, 195, 5, 5, EPD_BLACK);
    gfx.fillRect(0, 195, 5, 5, EPD_BLACK);
    gfx.writeMemory();
    epd.display();

    Serial.println("Sleeping");
    epd.sleep();

    Serial.println("Done.");
    while (1) { }
#endif
}
