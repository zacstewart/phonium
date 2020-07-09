#include "Waveshare_GFX.h"

Waveshare_GFX::Waveshare_GFX(Waveshare_EPD *epd, int16_t width, int16_t height)
    : Adafruit_GFX(width, height)
    , epd(epd)
    , width(width)
    , height(height)
{
    int16_t imageSize = width * height / 8;
    image = (unsigned char *) malloc(imageSize * sizeof(unsigned char));
    // Start out with a pure white image
    memset(this->image, 0xFF, imageSize);
}

void Waveshare_GFX::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    if (color) {
        image[(x + y * width) / 8] |= 0x80 >> (x % 8);
    } else {
        image[(x + y * width) / 8] &= ~(0x80 >> (x % 8));
    }
}

// TODO: optimize only writing the portion of memory that has changed since
// last write
void Waveshare_GFX::writeMemory() {
    epd->writeMemory(image);
}
