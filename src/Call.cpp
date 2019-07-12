#include "string.h"

#include "Call.h"

Call::Call(Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona)
: navigator(navigator)
, display(display)
, keypad(keypad)
, fona(fona)
, lastKey(NO_KEY)
, number("")
, callStart(0)
{
}

void Call::begin() {
  display->clearDisplay();
  display->setTextWrap(true);
  display->setTextColor(COLOR_BLACK);

  display->setCursor(0, 0);
  display->setTextSize(1);
  display->println("Ongoing call...");
  display->setTextSize(3);
  display->print(number);
  display->refresh();
}

void Call::handleKeyInput(KeyState state, KeypadEvent key) {
  // noop
}

void Call::update() {
  char key = keypad->getKey();
  if (key == lastKey) {
    return;
  }
  lastKey = key;

  switch (key) {
    case NO_KEY:
      break;
    case 'A':
    case 'B':
      break;
    case 'C':
      hangUp();
      break;
    case 'D':
      break;
    default:
      break;
  }
}

Call *Call::setNumber(char *num) {
  memcpy(number, num, sizeof(number));
  return this;
}

Call *Call::answerCall() {
  callStart = millis();
  Serial.print(F("Answreing call from "));
  Serial.println(number);
  fona->pickUp();
  return this;
}

Call *Call::initiateCall() {
  callStart = millis();
  Serial.print("Initiating call to ");
  Serial.println(number);
  fona->callPhone(number);
  return this;
}

void Call::hangUp() {
  Serial.println(F("Hanging up"));
  fona->hangUp();
  callEnded(); // TODO: this would actually happen as a result of callStatus
}

void Call::callEnded() {
  unsigned long callEnd = millis();
  char *duration = formatTime(callEnd - callStart);
  Serial.print("Call lasted ");
  Serial.println(duration);

  display->clearDisplay();
  display->setCursor(0, 0);
  display->setTextSize(1);
  display->println(F("Call ended"));
  display->setTextSize(3);
  display->print(duration);
  display->refresh();

  delay(2500);

  navigator->popController();
}
