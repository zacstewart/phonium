#include <Keypad.h>
#include "Adafruit_EPD.h"
#include <Adafruit_FONA.h>
#include <SoftwareSerial.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"
#include "Call.h"
#include "Dialer.h"

#define EPD_CS     10
#define EPD_DC     9
#define SRAM_CS    8
#define EPD_RESET  4
#define EPD_BUSY   A0 // can set to -1 to not use a pin (will wait a fixed delay)
#define DISPLAY_ROTATION 2 // Headers to the left
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4
#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

byte keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[KEYPAD_ROWS] = {A2, A3, A4, A5};
byte colPins[KEYPAD_COLS] = {A1, 5, 6, 7};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

Adafruit_SSD1608 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

/**
 * Controllers
 */
Navigator navigator = Navigator();

Dialer dialer = Dialer(&navigator, &display, &keypad);
Call call = Call(&navigator, &display, &keypad, &fona);

void setup() {
  Serial.begin(115200);
  Serial.println("Phonium starting");
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }

  Serial.println("Starting display");
  display.begin();
  display.setRotation(DISPLAY_ROTATION);
  Serial.println("Display started");
  
  navigator.setController(DIALER, &dialer);
  navigator.setController(CALL, &call);
  navigator.replaceController(DIALER);
  
  dialer.begin();
}

void loop() {
  navigator.currentController()->update();
}
