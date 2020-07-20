#include <Adafruit_SharpMem.h>

#include "Menu.h"

namespace Controllers {
    void Menu::begin() {
        Adafruit_GFX &canvas = services.getCanvas();
        Adafruit_SharpMem &display = services.getDisplay();

        display.clearDisplay();

        canvas.setTextColor(COLOR_BLACK);
        canvas.setCursor(0, 0);
        canvas.setTextSize(3);
        canvas.println("Menu");

        setLeftNavigationLabel("Back");
        setRightNavigationLabel("Select");

        display.refresh();
    }

    void Menu::handleKeyInput(KeyState state, KeypadEvent key) {
        switch (state) {
            case PRESSED:
                switch (key) {
                    case 'A':
                        navigator.popController();
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
}
