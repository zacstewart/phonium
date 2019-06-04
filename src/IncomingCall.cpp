#include <Adafruit_FONA.h>

#include "Call.h"
#include "IncomingCall.h"

IncomingCall::IncomingCall(Navigator *navigator, Adafruit_SSD1608 *display, Keypad *keypad, Adafruit_FONA *fona)
: navigator(navigator)
, display(display)
, keypad(keypad)
, fona(fona)
, number({'\0'})
{
}

void IncomingCall::begin() {
  display->clearBuffer();
  display->setTextWrap(true);
  display->setTextColor(COLOR_BLACK);

  display->setCursor(0, 0);
  display->setTextSize(1);
  display->println(F("Incoming call..."));
  display->setTextSize(3);
  display->print(number);
  display->display();
}

void IncomingCall::update() {
  switch (keypad->getKey()) {
    case 'B':
      answerCall();
      break;
    case 'C':
      hangUp();
      break;
    default:
      break;
  }

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
