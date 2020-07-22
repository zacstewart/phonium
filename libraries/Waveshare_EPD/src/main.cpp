#include <Arduino.h>

#include "Waveshare_EPD.h"
#include "Waveshare_GFX.h"

Waveshare_EPD epd = Waveshare_EPD(200, 200);
Waveshare_GFX gfx = Waveshare_GFX(&epd, 200, 200);

void testOptimizedWriteMemory() {
    Serial.println("Writing entire memory in one block");
    int start = millis();
    for (int i = 0; i < 10; i++) {
        gfx.fillRect(0, 0, 5, 5, EPD_BLACK);
        gfx.fillRect(195, 0, 5, 5, EPD_BLACK);
        gfx.fillRect(195, 195, 5, 5, EPD_BLACK);
        gfx.fillRect(0, 195, 5, 5, EPD_BLACK);
        gfx.writeMemory();
    }
    int duration = millis() - start;
    Serial.print("Took ");
    Serial.println(duration);

    Serial.println("Writing minimal amounts of memory necessary");
    start = millis();
    for (int i = 0; i < 10; i++) {
        gfx.fillRect(0, 0, 5, 5, EPD_BLACK);
        gfx.writeMemory();
        gfx.fillRect(195, 0, 5, 5, EPD_BLACK);
        gfx.writeMemory();
        gfx.fillRect(195, 195, 5, 5, EPD_BLACK);
        gfx.writeMemory();
        gfx.fillRect(0, 195, 5, 5, EPD_BLACK);
        gfx.writeMemory();
    }
    duration = millis() - start;
    Serial.print("Took ");
    Serial.println(duration);
}

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

    gfx.setRotation(EPD_ROTATION_270);

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

    Serial.println("Partial refresh");
    epd.displayModePartial();

    gfx.setCursor(0, 0);
    gfx.setTextColor(EPD_BLACK);
    for (char i = 'A'; i <= 'z'; i++) {
        gfx.print(i);
        gfx.writeMemory();
        epd.display();
    }

    Serial.println("Sleeping");
    epd.sleep();

    Serial.println("Done.");
    while (1) { }
#endif
}
