#ifndef WAVESHARE_GFX
#define WAVESHARE_GFX

#include <Adafruit_GFX.h>
#include "Waveshare_EPD.h"

class Waveshare_GFX : public Adafruit_GFX {
    Waveshare_EPD *epd;
    // Display dimensions
    int16_t width, height;
    // Memory area to writeMemory to
    int16_t xStart, yStart, xEnd, yEnd;
    unsigned char *image;

    public:
        Waveshare_GFX(Waveshare_EPD *, int16_t, int16_t);
        void writeMemory(void);

        // Adafruit_GFX
        void drawPixel(int16_t, int16_t, uint16_t);
};

#endif
