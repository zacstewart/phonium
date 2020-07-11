#include <Arduino.h>
#include <SPI.h>

#include "Waveshare_EPD.h"

Waveshare_EPD::Waveshare_EPD(int16_t width, int16_t height)
    : width(width)
    , height(height)
{
}

Waveshare_EPD::~Waveshare_EPD() {
}

void Waveshare_EPD::begin() {
    // Set up hardware interface
    pinMode(CS_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
    pinMode(DC_PIN, OUTPUT);
    pinMode(BUSY_PIN, INPUT);

    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));

    wake();
}

void Waveshare_EPD::wake() {
    // Initialize EPD
    reset();
    waitUntilIdle();

    // S/W reset
    sendCommand(CMD_SW_RESET);
    waitUntilIdle();

    // Driver output control
    sendCommand(CMD_DRIVER_OUTPUT_CONTROL);
    sendData(0xC7);
    sendData(0x00);
    sendData(0x00);

    // Data entry mode
    sendCommand(CMD_DATA_ENTRY_MODE);
    sendData(0b11); // Y increment, X increment

    // Border waveform?
    sendCommand(0x3C);
    sendData(0x01);

    // I don't even know
    sendCommand(0x18);
    sendData(0x80);

    // Load temperature and waveform setting?
    sendCommand(CMD_DISPLAY_UPDATE_CTRL_2);
    // 0xB1
    // - Enable clock signal
    // - Load temperature value
    // - Load LUT with DISPLAY Mode 1
    // - Disable clock signal
    sendData(0xB1);

    sendCommand(CMD_MASTER_ACTIVATION);
    waitUntilIdle();
}

void Waveshare_EPD::clear() {
    // TODO define these dims
    int w = 200 / 8;
    int h = 200;

    setMemoryArea(0, 0, 200, 200);
    setMemoryPointer(0, 0);

    sendCommand(CMD_WRITE_BW_RAM);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            sendData(0xFF);
        }
    }

    display();
}

void Waveshare_EPD::reset() {
    digitalWrite(RST_PIN, LOW);
    delay(10);
    digitalWrite(RST_PIN, HIGH);
    delay(10);
}

void Waveshare_EPD::sleep() {
    sendCommand(CMD_DEEP_SLEEP_MODE);
    sendData(0x01); // Enable
    delay(200);
    digitalWrite(RST_PIN, LOW);
}


/**
 * HIGH = busy
 * LOW = idle
 */
void Waveshare_EPD::waitUntilIdle() {
    while (digitalRead(BUSY_PIN) == HIGH) {
        delay(100);
    }
    delay(200);
}

/**
 * DC pin LOW for command
 */
void Waveshare_EPD::sendCommand(unsigned char command) {
    digitalWrite(DC_PIN, LOW);
    spiTransfer(command);
}

/**
 * DC pin HIGH for data
 */
void Waveshare_EPD::sendData(unsigned char command) {
    digitalWrite(DC_PIN, HIGH);
    spiTransfer(command);
}

void Waveshare_EPD::spiTransfer(unsigned char data) {
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(data);
    digitalWrite(CS_PIN, HIGH);
}

void Waveshare_EPD::setMemoryArea(int xStart, int yStart, int xEnd, int yEnd) {
    // Set RAM-X address start/end position
    sendCommand(CMD_SET_RAM_X_POSITIONS);
    sendData((xStart >> 3) & 0xFF);
    sendData((xEnd >> 3) & 0xFF);

    // Set RAM-Y address start/end position
    sendCommand(CMD_SET_RAM_Y_POSITIONS);
    sendData(yStart & 0xFF);
    sendData((yStart >> 8) & 0xFF);
    sendData(yEnd & 0xFF);
    sendData((yEnd >> 8) & 0xFF);
}

void Waveshare_EPD::setMemoryPointer(int x, int y) {
    sendCommand(CMD_SET_RAM_X_ADDRESS_COUNTER);
    sendData((x >> 3) & 0xFF);

    sendCommand(CMD_SET_RAM_Y_ADDRESS_COUNTER);
    sendData(y & 0xFF);
    sendData((y >> 8) & 0xFF);
    waitUntilIdle();
}

void Waveshare_EPD::writeMemory(
    unsigned char *image,
    int16_t xStart,
    int16_t yStart,
    int16_t xEnd,
    int16_t yEnd
) {
    if (
        xStart < 0 ||
        yStart < 0 ||
        xEnd >= width ||
        yEnd >= height
    ) {
        return;
    }

    // X coordinate must be multiple of 8 or we drop the last 3 bits
    xStart &= 0xF8;
    xEnd &= 0xF8;

    setMemoryArea(xStart, yStart, xEnd, yEnd);
    setMemoryPointer(xStart, yStart);
    sendCommand(CMD_WRITE_BW_RAM);

    // Recalculate x coordinates for indexing into the image array The compiler
    // might optimize these divisions away if I left them inline in the loop,
    // but I'm not sure.
    xStart /= 8;
    xEnd /= 8;
    int stride = width / 8;
    for (int y = yStart; y <= yEnd; y++) {
        for (int x = xStart; x <= xEnd; x++) {
            sendData(image[x + y * stride]);
        }
    }
}

void Waveshare_EPD::display() {
    sendCommand(CMD_DISPLAY_UPDATE_CTRL_2);
    // 0xF7
    // - Enable clock signal
    // - Enable Analog
    // - Load temperature value
    // - DISPLAY with DISPLAY Mode 1
    // - Disable Analog
    // - Disable OSC
    sendData(0xF7);
    sendCommand(CMD_MASTER_ACTIVATION);
    waitUntilIdle();
}
