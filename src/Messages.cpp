#include "Messages.h"
#include "Message.h"

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
      break;
    case 'D':
      // messages are 1-indexed
      ((Message *) navigator->getController(MESSAGE))
        ->setMessage(curMessage + 1);
      navigator->pushController(MESSAGE);
      return;
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

void Messages::loadMessages() {
  numMessages = fona->getNumSMS();
  if (numMessages < 1) {
    return;
  }
  curMessage = numMessages - 1;

  if (previews != NULL) {
    for (int8_t i = 0; i < numMessages; i++) {
      free(previews[i]);
    }
    free(previews);
  }
  previews = (char **) malloc(numMessages);

  uint16_t messageLen;
  for (int8_t i = 0; i < numMessages; i++) {
    // +1 for null terminator
    previews[i] = (char *) malloc(MESSAGE_PREVIEW_LENGTH + 1);
    // messages are 1-indexed
    fona->readSMS(i + 1, previews[i], MESSAGE_PREVIEW_LENGTH, &messageLen);
  }
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
