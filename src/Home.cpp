#include "Home.h"
#include "Dialer.h"
#include "Messages.h"

Home::Home(Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona)
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

  display->clearDisplay();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextSize(2);
  display->println(numSms);
  display->setTextSize(1);
  display->print("unread messages");
  display->refresh();
}

void Home::handleKeyInput(KeyState state, KeypadEvent key) {
  // noop
}

void Home::update() {
  char key = keypad->getKey();

  if (!keypad->keyStateChanged()) {
    return;
  }

  switch (key) {
    case NO_KEY:
      break;
    case 'A':
      ((Messages *) navigator->getController(MESSAGES))
        ->loadMessages();
      navigator->pushController(MESSAGES);
      return;
    case 'B':
    case 'C':
    case 'D':
      break;
    default:
      startDialing(key);
      return;
  }
}

void Home::startDialing(char key) {
  Serial.print(F("Dialing ")); Serial.println(key);
  char number[2] = {key, '\0'};
  ((Dialer *) navigator->getController(DIALER))->setNumber(number);
  navigator->pushController(DIALER);
}
