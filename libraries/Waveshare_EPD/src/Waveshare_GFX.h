#ifndef WAVESHARE_GFX
#define WAVESHARE_GFX

#include <Adafruit_GFX.h>
#include "Waveshare_EPD.h"

class Waveshare_GFX : public Adafruit_GFX {
    int16_t width, height;
    unsigned char *image;
    Waveshare_EPD *epd;

    public:
        Waveshare_GFX(Waveshare_EPD *, int16_t, int16_t);
        void writeMemory(void);

        // Adafruit_GFX
        void drawPixel(int16_t, int16_t, uint16_t);
};

#endif
