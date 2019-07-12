#include <Adafruit_FONA.h>

#include "Call.h"
#include "IncomingCall.h"

IncomingCall::IncomingCall(Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona)
: navigator(navigator)
, display(display)
, keypad(keypad)
, fona(fona)
, number("")
{
}

void IncomingCall::begin() {
  display->clearDisplay();
  display->setTextWrap(true);
  display->setTextColor(COLOR_BLACK);

  display->setCursor(0, 0);
  display->setTextSize(1);
  display->println(F("Incoming call..."));
  display->setTextSize(3);
  display->print(number);
  display->refresh();
}

void IncomingCall::handleKeyInput(KeyState state, KeypadEvent key) {
  switch (state) {
    case PRESSED:
      switch (key) {
        case 'B':
          answerCall();
          break;
        case 'C':
          hangUp();
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void IncomingCall::update() {
  keypad->getKeys();

  switch (fona->getCallStatus()) {
    case FONA_CALL_READY: // Stopped ringing
      navigator->popController();
      break;
    case FONA_CALL_FAILED:
    case FONA_CALL_UNKNOWN:
    case FONA_CALL_RINGING:
    case FONA_CALL_INPROGRESS: // Should this nav to Call?
    default:
      break;
  }
}

void IncomingCall::answerCall() {
  Call *call = (Call *) navigator->getController(CALL);
  call->setNumber(number)->answerCall();
  navigator->replaceController(CALL);
}

void IncomingCall::hangUp() {
  fona->hangUp();
}
