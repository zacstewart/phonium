#ifndef WAVESHARE_GFX
#define WAVESHARE_GFX

#include <Adafruit_GFX.h>
#include "Waveshare_EPD.h"

#define EPD_ROTATION_0      0
#define EPD_ROTATION_90     1
#define EPD_ROTATION_180    2
#define EPD_ROTATION_270    3

class Waveshare_GFX : public Adafruit_GFX {
    Waveshare_EPD *epd;
    // Display dimensions
    int16_t width, height;
    // Memory area to writeMemory to
    int16_t xStart, yStart, xEnd, yEnd;
    unsigned char *image;
    uint8_t rotation;

    public:
        Waveshare_GFX(Waveshare_EPD *, int16_t, int16_t);
        void clear(void);
        void setRotation(uint8_t);
        void writeMemory(void);

        // Adafruit_GFX
        void drawPixel(int16_t, int16_t, uint16_t);
};

#endif
