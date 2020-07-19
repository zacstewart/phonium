#include <Adafruit_SharpMem.h>

#include "Menu.h"

void Menu::begin() {
    Adafruit_SharpMem &display = services.getDisplay();
    display.clearDisplay();
    display.setTextColor(COLOR_BLACK);

    display.setCursor(0, 0);
    display.setTextSize(3);
    display.println("Menu");

    setLeftNavigationLabel("Back");
    setRightNavigationLabel("Select");

    display.refresh();
}

void Menu::handleKeyInput(KeyState state, KeypadEvent key) {
    switch (state) {
        case PRESSED:
            switch (key) {
                case 'A':
                    navigator->popController();
                    return;
                case 'B':
                case 'C':
                case 'D':
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Menu::update() {
}
