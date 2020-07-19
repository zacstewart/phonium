#include <Adafruit_SharpMem.h>

#include "Dialer.h"
#include "Home.h"
#include "Menu.h"
#include "Messages.h"

void Home::begin() {
    int8_t numSms = services.getFona().getNumSMS();

    Serial.print(numSms);
    Serial.println(F(" unread SMSs"));

    Adafruit_SharpMem &display = services.getDisplay();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(COLOR_BLACK);
    display.setTextSize(2);
    display.println(numSms);
    display.setTextSize(1);
    display.print("unread messages");

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
