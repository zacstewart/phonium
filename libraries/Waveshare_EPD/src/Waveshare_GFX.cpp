#include <algorithm>

#include "Waveshare_GFX.h"

Waveshare_GFX::Waveshare_GFX(Waveshare_EPD *epd, int16_t width, int16_t height)
    : Adafruit_GFX(width, height)
    , epd(epd)
    , width(width)
    , height(height)
    , xStart(-1)
    , yStart(-1)
    , xEnd(-1)
    , yEnd(-1)
    , rotation(EPD_ROTATION_0)
{
    int16_t imageSize = width * height / 8;
    image = (unsigned char *) malloc(imageSize * sizeof(unsigned char));
    // Start out with a pure white image
    memset(this->image, 0xFF, imageSize);
}

void Waveshare_GFX::setRotation(uint8_t rot) {
    if (rot > EPD_ROTATION_270) {
        return;
    }
    rotation = rot;
}

/**
 * Writes the canvas image into the memory of the EPD.
 */
void Waveshare_GFX::writeMemory() {
    epd->writeMemory(image, 0, 0, width - 1, height - 1);
}

/*******************************************************************************
 *
 * Adafruit_GFX implementation
 *
 ******************************************************************************/

/**
 * Draws a single pixel onto the canvas area. It does not interact with the
 * EPD immediately; you will need to call `writeMemory` to transfer memory
 * and then call `display` on the EPD driver.
 */
void Waveshare_GFX::drawPixel(int16_t x, int16_t y, uint16_t color) {
    switch(rotation) {
        case EPD_ROTATION_0:
            break;
        case EPD_ROTATION_90:
            std::swap(x, y);
            x = width - x - 1;
            break;
        case EPD_ROTATION_180:
            y = height - y - 1;
            x = width - x - 1;
            break;
        case EPD_ROTATION_270:
            std::swap(x, y);
            y = height - y - 1;
            break;
        default:
            break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    // Keep track of the canvas area that has changed. This will help us
    // determine if it would be optimal to do a partial or full refresh
    if (xStart == -1 || x < xStart) {
        xStart = x;
    }
    if (yStart == -1 || y < yStart) {
        yStart = y;
    }
    if (xEnd < x) {
        xEnd = x;
    }
    if (yEnd < y) {
        yEnd = y;
    }

    if (color) {
        image[(x + y * width) / 8] |= 0x80 >> (x % 8);
    } else {
        image[(x + y * width) / 8] &= ~(0x80 >> (x % 8));
    }
}
