#include "Message.h"

Message::Message(Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona)
: navigator(navigator)
, display(display)
, keypad(keypad)
, fona(fona)
, message(SmsMessage { 0 })
{
}

void Message::begin() {
  display->clearDisplay();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextSize(2);
  display->println(message.sender);
  display->setTextSize(1);
  display->println(message.message);
  display->refresh();
}

void Message::update() {
  char key = keypad->getKey();

  // Key is being held
  if (!keypad->keyStateChanged()) {
    return;
  }

  switch (key) {
    case 'A':
      navigator->popController();
      return;
    case 'B':
    case 'C':
      break;
    case 'D':
      return;
    default:
      break;
  }
}

void Message::setMessage(uint8_t index) {
  message.index = index;
  uint16_t messageLen;
  fona->readSMS(index, message.message, MESSAGE_LENGTH, &messageLen);
  fona->getSMSSender(index, message.sender, NUMBER_LENGTH);
}
