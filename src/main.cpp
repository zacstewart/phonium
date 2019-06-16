#include <Keypad.h>
#include <Adafruit_EPD.h>
#include <Adafruit_FONA.h>
#include <HardwareSerial.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

#include "Call.h"
#include "ComposeMessage.h"
#include "Dialer.h"
#include "IncomingCall.h"
#include "Home.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define EPD_CS     4
#define EPD_DC     5
#define SRAM_CS    6
#define EPD_RESET  2
#define EPD_BUSY   8
#define DISPLAY_ROTATION 2 // Headers to the left

#define FONA_RI  3
#define FONA_RST 2
#define FONA_BAUD_RATE 4800

byte keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[KEYPAD_ROWS] = {18, 19, 20, 21};
byte colPins[KEYPAD_COLS] = {17, 16, 15, 14};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

Adafruit_SSD1608 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

HardwareSerial *fonaSerial = &Serial1;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

/**
 * Controllers
 */
Navigator navigator = Navigator();

Home home = Home(&navigator, &display, &keypad);
Dialer dialer = Dialer(&navigator, &display, &keypad);
Call call = Call(&navigator, &display, &keypad, &fona);
IncomingCall incomingCall = IncomingCall(&navigator, &display, &keypad, &fona);
ComposeMessage composeMessage = ComposeMessage(&navigator, &display, &keypad, &fona);

#ifdef USING_MAKEFILE
extern "C" int main(void) {
    setup();
    while (1) {
        loop();
        yield();
    }
}
#endif

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

  navigator.setController(CALL, &call);
  navigator.setController(COMPOSE_MESSAGE, &composeMessage);
  navigator.setController(DIALER, &dialer);
  navigator.setController(INCOMING_CALL, &incomingCall);
  navigator.setController(HOME, &home);

  Serial.println(F("Phonium ready"));
  navigator.replaceController(HOME);
}

void loop() {
  if (fona.incomingCallNumber(incomingCall.number)) {
    navigator.pushController(INCOMING_CALL);
  }
  navigator.currentController()->update();
}
