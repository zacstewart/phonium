#include "Home.h"
#include "Dialer.h"

Home::Home(Navigator *navigator, Adafruit_SSD1608 *display, Keypad *keypad)
: navigator(navigator)
, display(display)
, keypad(keypad)
{
}

void Home::begin() {
}

void Home::update() {
  char key = keypad->getKey();

  switch (key) {
    case NO_KEY:
    case 'A':
    case 'B':
    case 'C':
    case 'D':
      break;
    default:
      startDialing(key);
  }
}

void Home::startDialing(char key) {
  Serial.print("Dialing "); Serial.println(key);
  char number[2] = {key, '\0'};
  ((Dialer *) navigator->getController(DIALER))->setNumber(number);
  navigator->pushController(DIALER);
}
