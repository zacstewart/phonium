#include "Messages.h"

#define MESSAGE_PREVIEW_LENGTH 12

Messages::Messages(Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona)
: navigator(navigator)
, display(display)
, keypad(keypad)
, fona(fona)
, numMessages(0)
, previews(NULL)
, curMessage(0)
{
}

void Messages::begin() {
  numMessages = fona->getNumSMS();
  if (numMessages < 1) {
    return;
  }
  curMessage = numMessages - 1;

  if (previews != NULL) {
    Serial.println("freeing previous previews");
    for (int8_t i = 0; i < numMessages; i++) {
      free(previews[i]);
    }
    free(previews);
  }
  Serial.println("malloc");
  previews = malloc(numMessages * MESSAGE_PREVIEW_LENGTH);

  uint16_t messageLen;
  for (int8_t i = 0; i < numMessages; i++) {
    // +1 for null byte
    previews[i] = malloc(MESSAGE_PREVIEW_LENGTH + 1);
    // messages are 1-indexed
    fona->readSMS(i + 1, previews[i], MESSAGE_PREVIEW_LENGTH, &messageLen);
  }

  draw();
}

void Messages::update() {
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
    case 'D':
      break;
    case '2':
      cursorUp();
      break;
    case '8':
      cursorDown();
      break;
    default:
      break;
  }

  draw();
}

void Messages::draw() {
  display->clearDisplay();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextSize(2);
  for (int8_t i = numMessages - 1; i >= 0; i--) {
    if (i == curMessage) {
      display->print(">");
    } else {
      display->print(" ");
    }
    display->println(previews[i]);
  }
  display->refresh();
}

void Messages::cursorDown()
{
  if (curMessage <= 0) {
    return;
  }

  --curMessage;
}

void Messages::cursorUp()
{
  if (curMessage >= (numMessages - 1)) {
    return;
  }

  ++curMessage;
}
