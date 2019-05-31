#include <Keypad.h>
#include "Adafruit_EPD.h"
#include <Adafruit_FONA.h>
#include <SoftwareSerial.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"
#include "Call.h"
#include "Dialer.h"
#include "IncomingCall.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define EPD_CS     10
#define EPD_DC     9
#define SRAM_CS    8
#define EPD_RESET  7
#define EPD_BUSY   4
#define DISPLAY_ROTATION 2 // Headers to the left

#define FONA_RX 5
#define FONA_TX 6
#define FONA_RI 3
#define FONA_RST 7

byte keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[KEYPAD_ROWS] = {A4, A5, 2, 0};
byte colPins[KEYPAD_COLS] = {A3, A2, A1, A0};
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
IncomingCall incomingCall = IncomingCall(&navigator, &display, &keypad, &fona);

void setup() {
  while (!Serial);

  Serial.begin(115200);
  Serial.println(F("Phonium starting"));

  Serial.println(F("Starting display"));
  display.begin();
  display.setRotation(DISPLAY_ROTATION);

  Serial.println(F("Starting cellular"));
  fonaSerial->begin(FONA_BAUD_RATE);
  if (!fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
  }
  fona.callerIdNotification(true, digitalPinToInterrupt(FONA_RI));
  
  navigator.setController(DIALER, &dialer);
  navigator.setController(CALL, &call);
  navigator.setController(INCOMING_CALL, &incomingCall);
  navigator.replaceController(DIALER);
}

void loop() {
  if (fona.incomingCallNumber(incomingCall.number)) {
    navigator.pushController(INCOMING_CALL);
  }
  navigator.currentController()->update();
}
