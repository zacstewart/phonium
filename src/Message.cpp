#include <Adafruit_SharpMem.h>

#include "ComposeMessage.h"
#include "Message.h"

Message::Message(Services &services, Navigator &navigator):
    Controller(services, navigator),
    message(SmsMessage { 0, NULL })
{
}

void Message::begin() {
    Adafruit_SharpMem &display = services.getDisplay();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(COLOR_BLACK);
    display.setTextSize(2);
    display.println(message.sender);
    display.setTextSize(1);
    display.println(message.message);

    setLeftNavigationLabel("Back");
    setRightNavigationLabel("Reply");

    display.refresh();
}

void Message::handleKeyInput(KeyState state, KeypadEvent key) {
    switch (state) {
        case PRESSED:
            switch (key) {
                case 'A':
                    navigator.popController();
                    return;
                case 'B':
                case 'C':
                    break;
                case 'D':
                    ((ComposeMessage *) navigator.getController(COMPOSE_MESSAGE))
                        ->setNumber(message.sender);
                    navigator.pushController(COMPOSE_MESSAGE);
                    return;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Message::update() {
}

void Message::setMessage(uint8_t index) {
    message.index = index;
    uint16_t messageLen;
    message.message = (char *) malloc(sizeof(char) * MESSAGE_LENGTH + 1);
    services.getFona().readSMS(index, message.message, MESSAGE_LENGTH, &messageLen);
    realloc(message.message, sizeof(char) * messageLen);
    services.getFona().getSMSSender(index, message.sender, NUMBER_LENGTH);
}
