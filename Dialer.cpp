#include "Dialer.h"
#include "Call.h"

#define FONT_SIZE 3
#define CHAR_WIDTH 5 * FONT_SIZE
#define CHAR_HEIGHT 8 * FONT_SIZE

Dialer::Dialer(Navigator *navigator, Adafruit_SSD1608 *display, Keypad *keypad)
: navigator(navigator)
, display(display)
, keypad(keypad)
, lastKey('\0')
, number({'\0'})
, cur(0)
{
}

void Dialer::begin() {
  display->clearBuffer();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextWrap(true);
  display->setTextSize(3);
  display->display();
}

void Dialer::update() {
  char key = keypad->getKey();
  if (key == lastKey) {
    return;
  }
  lastKey = key;

  Serial.print(F("Pressed "));
  Serial.println(key);

  switch (key) {
    case NO_KEY:
      break;
    case 'A':
      backspace();
      break;
    case 'B':
      callNumber();
    case 'C':
    case 'D':
      break;
    default:
      number[cur++] = key;
      display->clearBuffer();
      display->setCursor(0, 0);
      display->setTextColor(COLOR_BLACK);
      display->print(number);
      display->display();
  }
}

void Dialer::backspace() {
    number[--cur] = '\0';
    int left = cur * (CHAR_WIDTH + FONT_SIZE);
    display->fillRect(left, 0, CHAR_WIDTH, CHAR_HEIGHT, EPD_INVERSE);
    display->display();
}

void Dialer::callNumber() {
  Serial.print(F("Caling "));
  Serial.print(number);
  Serial.println(F("..."));
  Call *call = (Call *) navigator->getController(CALL);
  call->setNumber(number)->initiateCall();
  navigator->pushController(CALL);

  memset(number, '\0', sizeof(number));
  cur = 0;
}
