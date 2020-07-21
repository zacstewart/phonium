
#include "Dialer.h"
#include "Home.h"
#include "Menu.h"
#include "Messages.h"

namespace Controllers {
    void Home::begin() {
        int8_t numSms = services.getFona().getNumSMS();

        Serial.print(numSms);
        Serial.println(F(" unread SMSs"));

        Display &display = services.getDisplay();
        Adafruit_GFX &canvas = display.getCanvas();

        display.clear();

        canvas.setCursor(0, 0);
        canvas.setTextColor(COLOR_BLACK);
        canvas.setTextSize(2);
        canvas.println(numSms);
        canvas.setTextSize(1);
        canvas.print("unread messages");

        setLeftNavigationLabel("Messages");
        setRightNavigationLabel("Menu");

        display.refresh();
    }

    void Home::handleKeyInput(KeyState state, KeypadEvent key) {
        switch (state) {
            case PRESSED:
                switch (key) {
                    case 'A':
                        navigator.pushController(MESSAGES);
                        return;
                    case 'B':
                    case 'C':
                        break;
                    case 'D':
                        navigator.pushController(MENU);
                        return;
                    default:
                        startDialing(key);
                        return;
                }
                break;
            default:
                break;
        }
    }

    void Home::update() {
    }

    void Home::startDialing(char key) {
        Serial.print(F("Dialing ")); Serial.println(key);
        char number[2] = {key, '\0'};
        ((Dialer *) navigator.getController(DIALER))->setNumber(number);
        navigator.pushController(DIALER);
    }
}
