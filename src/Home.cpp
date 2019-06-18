#include "Home.h"
#include "Dialer.h"

Home::Home(Navigator *navigator, Adafruit_SSD1608 *display, Keypad *keypad, Adafruit_FONA *fona)
: navigator(navigator)
, display(display)
, keypad(keypad)
, fona(fona)
{
}

void Home::begin() {
  int8_t numSms = fona->getNumSMS();

  Serial.print(numSms);
  Serial.println(F(" unread SMSs"));

  display->clearBuffer();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextSize(2);
  display->println(numSms);
  display->setTextSize(1);
  display->print("unread messages");
  display->display();
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
