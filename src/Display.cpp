#include "Display.h"

Display::Display(Waveshare_GFX &canvas, Waveshare_EPD &device):
    canvas(canvas),
    device(device)
{
}

void Display::clear() {
    canvas.clear();
}

Adafruit_GFX &Display::getCanvas() {
    return canvas;
}

void Display::refresh() {
    writeCanvasMemory();
    device.display();
}

void Display::partialRefresh() {
}

void Display::writeCanvasMemory() {
    canvas.writeMemory();
}
