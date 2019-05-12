#include <Keypad.h>
#include "Adafruit_EPD.h"

#include "Common.h"
#include "Controller.h"
#include "Dialer.h"

#define EPD_CS     10
#define EPD_DC     9
#define SRAM_CS    8
#define EPD_RESET  A0
#define EPD_BUSY   A1 // can set to -1 to not use a pin (will wait a fixed delay)
#define DISPLAY_ROTATION 2 // Headers to the left
#define COLOR_BLACK EPD_BLACK
#define COLOR_GRAY EPD_RED
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

byte keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[KEYPAD_ROWS] = {3, 2, A2, A3};
byte colPins[KEYPAD_COLS] = {4, 5, 6, 7};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

Adafruit_SSD1608 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

Dialer dialer = Dialer(&display, &keypad);

void setup() {
  Serial.begin(115200);
  Serial.println("Phonium starting");
  display.begin();
  display.setRotation(DISPLAY_ROTATION);
  dialer.begin();
}

void loop() {
  dialer.update();
}
