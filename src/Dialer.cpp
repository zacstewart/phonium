#include "Dialer.h"
#include "Call.h"
#include "ComposeMessage.h"

#define FONT_SIZE 3
#define CHAR_WIDTH 5 * FONT_SIZE
#define CHAR_HEIGHT 8 * FONT_SIZE

Dialer::Dialer(Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona)
: Controller(navigator, display, keypad, fona)
, lastKey(NO_KEY)
, number("")
, cur(0)
{
}

void Dialer::begin() {
  draw();
}

void Dialer::handleKeyInput(KeyState state, KeypadEvent key) {
  switch (state) {
    case PRESSED:
      switch (key) {
        case NO_KEY:
          break;
        case 'A':
          if (cur > 0) {
            backspace();
          }

          if (cur == 0) {
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
      break;
    default:
      break;
  }
}

void Dialer::update() {
}

void Dialer::setNumber(char *num) {
  memset(number, '\0', sizeof(number));
  strcpy(number, num);
  cur = strlen(num);
}

inline void Dialer::backspace() {
  number[--cur] = '\0';
  draw();
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
  display->clearDisplay();
  display->setTextColor(COLOR_BLACK);
  display->setTextSize(3);
  display->setCursor(0, 0);
  display->print(number);

  setLeftNavigationLabel("Delete");
  setRightNavigationLabel("Message");

  display->refresh();
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
