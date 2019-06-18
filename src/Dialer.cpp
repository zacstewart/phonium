#include "Dialer.h"
#include "Call.h"
#include "ComposeMessage.h"

#define FONT_SIZE 3
#define CHAR_WIDTH 5 * FONT_SIZE
#define CHAR_HEIGHT 8 * FONT_SIZE

Dialer::Dialer(Navigator *navigator, Adafruit_SSD1608 *display, Keypad *keypad)
: navigator(navigator)
, display(display)
, keypad(keypad)
, lastKey(NO_KEY)
, number("")
, cur(0)
{
}

void Dialer::begin() {
  draw();
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
      if (cur > 0) {
        backspace();
      } else {
        navigator->popController();
      }
      break;
    case 'B':
      callNumber();
    case 'C':
      break;
    case 'D':
      textNumber();
      break;
    default:
      number[cur++] = key;
      draw();
  }
}

void Dialer::setNumber(char *num) {
  memset(number, '\0', sizeof(number));
  memcpy(number, num, sizeof(num));
  cur = strlen(num);
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
  navigator->replaceController(CALL);

  reset();
}

void Dialer::draw() {
  display->clearBuffer();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextSize(3);
  display->print(number);
  display->display();
}

void Dialer::reset() {
  memset(number, '\0', sizeof(number));
  cur = 0;
  lastKey = NO_KEY;
}

void Dialer::textNumber() {
  ComposeMessage *compose = (ComposeMessage *) navigator->getController(COMPOSE_MESSAGE);
  compose->setNumber(number);
  navigator->replaceController(COMPOSE_MESSAGE);

  reset();
}
