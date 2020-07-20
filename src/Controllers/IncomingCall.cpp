#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>

#include "Call.h"
#include "IncomingCall.h"

namespace Controllers {
    IncomingCall::IncomingCall(Services &services, Navigator &navigator):
        Controller(services, navigator),
        number("")
    {
    }

    void IncomingCall::begin() {
        Adafruit_GFX &canvas = services.getCanvas();
        Adafruit_SharpMem &display = services.getDisplay();

        display.clearDisplay();

        canvas.setTextWrap(true);
        canvas.setTextColor(COLOR_BLACK);

        canvas.setCursor(0, 0);
        canvas.setTextSize(1);
        canvas.println(F("Incoming call..."));
        canvas.setTextSize(3);
        canvas.print(number);

        display.refresh();
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
        switch (services.getFona().getCallStatus()) {
            case FONA_CALL_READY: // Stopped ringing
                navigator.popController();
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
        Call *call = (Call *) navigator.getController(CALL);
        call->setNumber(number)->answerCall();
        navigator.replaceController(CALL);
    }

    void IncomingCall::hangUp() {
        services.getFona().hangUp();
    }
}
