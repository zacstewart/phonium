#include "Common.h"

#include "Messages.h"
#include "Message.h"

// TODO: this needs to be based on how wide the screen is
#define MESSAGE_PREVIEW_LENGTH 12

Messages::Messages(Services *services, Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona):
    Controller(services, navigator, display, keypad, fona),
    numMessages(0),
    curMessage(0)
{
}

void Messages::setServices(Services *services) {
    this->services = services;
}

void Messages::begin() {
    Messaging *messaging = services->getMessaging();
    numMessages = messaging->messages->length;
    curMessage = messaging->messages->head->value->index;
    draw();
}

void Messages::handleKeyInput(KeyState state, KeypadEvent key) {
    switch (state) {
        case PRESSED:
            switch (key) {
                case 'A':
                    navigator->popController();
                    return;
                case 'B':
                case 'C':
                    break;
                case 'D':
                    ((Message *) navigator->getController(MESSAGE))
                        ->setMessage(curMessage);
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
            break;
        default:
            break;
    }
}

void Messages::update() {
}

void Messages::draw() {
    display->clearDisplay();
    display->setCursor(0, 0);
    display->setTextColor(COLOR_BLACK);
    display->setTextSize(2);

    char preview[MESSAGE_PREVIEW_LENGTH + 1];

    Messaging *messaging = services->getMessaging();
    Element *it = messaging->messages->head;
    while(it) {
        if (it->value->index == curMessage) {
            display->print(">");
        } else {
            display->print(" ");
        }
        substr(preview, it->value->message, MESSAGE_PREVIEW_LENGTH);
        display->println(preview);
        it = it->next;
    }

    setLeftNavigationLabel("Back");
    setRightNavigationLabel("Read");

    display->refresh();
}

void Messages::cursorDown() {
    if (curMessage <= 0) {
        return;
    }

    --curMessage;
}

void Messages::cursorUp() {
    if (curMessage > (numMessages - 1)) {
        return;
    }

    ++curMessage;
}
