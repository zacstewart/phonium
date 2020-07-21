#include "Display.h"

Display::Display(Adafruit_GFX &canvas, Adafruit_SharpMem &device):
    canvas(canvas),
    device(device)
{
}

void Display::clear() {
    device.clearDisplay();
}

Adafruit_GFX &Display::getCanvas() {
    return canvas;
}

void Display::refresh() {
    device.refresh();
}

void Display::partialRefresh() {
}

void Display::writeCanvasMemory() {
}
