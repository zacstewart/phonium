#include "string.h"

#include "Call.h"

namespace Controllers {
    Call::Call(Services &services, Navigator &navigator):
        Controller(services, navigator),
        lastKey(NO_KEY),
        number(""),
        callStart(0)
    {
    }

    void Call::begin() {
        Display &display = services.getDisplay();
        Adafruit_GFX &canvas = display.getCanvas();

        display.clear();

        canvas.setTextWrap(true);
        canvas.setTextColor(COLOR_BLACK);

        canvas.setCursor(0, 0);
        canvas.setTextSize(1);
        canvas.println("Ongoing call...");
        canvas.setTextSize(3);
        canvas.print(number);

        display.refresh();
    }

    void Call::handleKeyInput(KeyState state, KeypadEvent key) {
        switch (state) {
            case PRESSED:
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
                break;
            default:
                break;
        }
    }

    void Call::update() {
    }

    Call *Call::setNumber(char *num) {
        memset(number, '\0', sizeof(number));
        strcpy(number, num);
        return this;
    }

    Call *Call::answerCall() {
        callStart = millis();
        Serial.print(F("Answreing call from "));
        Serial.println(number);
        services.getFona().pickUp();
        return this;
    }

    Call *Call::initiateCall() {
        callStart = millis();
        Serial.print("Initiating call to ");
        Serial.println(number);
        services.getFona().callPhone(number);
        return this;
    }

    void Call::hangUp() {
        Serial.println(F("Hanging up"));
        services.getFona().hangUp();
        callEnded(); // TODO: this would actually happen as a result of callStatus
    }

    void Call::callEnded() {
        unsigned long callEnd = millis();
        char *duration = formatTime(callEnd - callStart);
        Serial.print("Call lasted ");
        Serial.println(duration);

        Display &display = services.getDisplay();
        Adafruit_GFX &canvas = display.getCanvas();
        display.clear();
        canvas.setCursor(0, 0);
        canvas.setTextSize(1);
        canvas.println(F("Call ended"));
        canvas.setTextSize(3);
        canvas.print(duration);
        display.refresh();

        delay(2500);

        navigator.popController();
    }
}
