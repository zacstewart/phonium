#include "Dialer.h"

#define COLOR_WHITE EPD_WHITE
#define COLOR_BLACK EPD_BLACK
#define COLOR_GRAY EPD_RED
#define FONT_SIZE 3
#define CHAR_WIDTH 5 * FONT_SIZE
#define CHAR_HEIGHT 8 * FONT_SIZE

Dialer::Dialer(Adafruit_SSD1608 *display, Keypad *keypad)
: display(display)
, keypad(keypad)
, last_key('\0')
, cur(0)
{
}

void Dialer::begin() {
  display->clearBuffer();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextWrap(true);
  display->setTextSize(3);
  display->clearDisplay();
}

void Dialer::update() {
  char key = keypad->getKey();
  if (key == last_key) {
    return;
  }
  last_key = key;

  Serial.print("Pressed ");
  Serial.println(key);

  switch (key) {
    case NO_KEY:
      break;
    case 'A':
      backspace();
      break;
    case 'B':
    case 'C':
      callNumber();
    case 'D':
      break;
    default:
      number[cur] = key;
      cur++;
      display->clearBuffer();
      display->setCursor(0, 0);
      display->setTextColor(COLOR_BLACK);
      display->print(number);
      display->display();
  }
}

void Dialer::backspace() {
    cur--;
    number[cur] = '\0';
    int left = cur * (CHAR_WIDTH + 3);
    display->fillRect(left, 0, CHAR_WIDTH, CHAR_HEIGHT, EPD_INVERSE);
    display->display();
}

void Dialer::callNumber() {
  Serial.print("Caling ");
  Serial.print(number);
  Serial.println("...");
}
