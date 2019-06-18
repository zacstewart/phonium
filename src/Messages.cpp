#include "Messages.h"

Messages::Messages(Navigator *navigator, Adafruit_SSD1608 *display, Keypad *keypad, Adafruit_FONA *fona)
: navigator(navigator)
, display(display)
, keypad(keypad)
, fona(fona)
{
}

void Messages::begin()
{
  Serial.println("Getting message.");
  char messageBuf[MESSAGE_LENGTH];
  uint16_t messageLen;
  fona->readSMS(1, messageBuf, MESSAGE_LENGTH, &messageLen);
  Serial.println(messageBuf);

  display->clearBuffer();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextSize(1);
  display->print(messageBuf);
  display->display();
}

void Messages::update()
{
}
