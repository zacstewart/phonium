#include "string.h"
#include <Adafruit_SharpMem.h>

#include "ComposeMessage.h"

#define INPUT_CYCLE_TIMEOUT 1000
#define NO_CHAR_SET -1

typedef struct CharSet {
    uint8_t length;
    const char *unmodified;
    const char *modified;
} CharSet;

const CharSet KEY_TO_CHARS[12] = {
    {5, "0-+<>", "0-+<>"},
    {5, "1.,?!", "1.,?!"},
    {4, "2abc", "2ABC"},
    {4, "3def", "3DEF"},
    {4, "4ghi", "4GHI"},
    {4, "5jkl", "5JKL"},
    {4, "6mno", "6MNO"},
    {5, "7pqrs", "7PQRS"},
    {4, "8tuv", "8TUV"},
    {5, "9wxyz", "9WXYZ"},
    {2, "* ", "* "},
    {1, "#", "#"}
};

namespace Controllers {
    ComposeMessage::ComposeMessage(Services &services, Navigator &navigator):
        Controller(services, navigator),
        lastKey(NO_KEY),
        lastCharSet(NO_CHAR_SET),
        lastInputAt(0),
        curChar(1),
        number(""),
        message(""),
        cur(0)
    {
    }

    void ComposeMessage::begin() {
        draw();
    }

    void ComposeMessage::handleKeyInput(KeyState state, KeypadEvent key) {
        switch (state) {
            case IDLE:
                break;
            case RELEASED:
                break;
            case PRESSED:
                switch (key) {
                    case NO_KEY:
                        break;
                    case 'A':
                        if (cur == 0 && message[cur] == '\0') {
                            navigator.popController();
                        } else {
                            backspace();
                        }
                        break;
                    case 'B':
                    case 'C':
                        break;
                    case 'D':
                        sendMessage();
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        handleTextEntry((uint8_t) key - '0');
                        break;
                    case '*':
                        handleTextEntry(10);
                        break;
                    case '#':
                        handleTextEntry(11);
                        break;
                    default:
                        break;
                }
                break;
            case HOLD:
                break;
        }
    }

    void ComposeMessage::update() {
    }

    void ComposeMessage::setNumber(char *num) {
        memset(number, '\0', sizeof(number));
        strcpy(number, num);
    }

    /**
     * Deletes the char under cursor if timeout has not occurred,
     * otherwise, moves the cursor one place to the left and deletes
     * that char. Resets the char set and current char of that set.
     *
     * Will blindly recede the cursor to negative indexes, so you must
     * ensure that cur is > 0 before calling backspace.  Guarding that
     * cur is > 0 here would potentially waste an extra CPU cycle.
     */
    void ComposeMessage::backspace() {
        lastCharSet = NO_CHAR_SET;
        curChar = 1;
        if (message[cur] == '\0') {
            --cur;
        }
        message[cur] = '\0';
        draw();
    }

    void ComposeMessage::draw() {
        Serial.print(F("Message: '")); Serial.print(message); Serial.println(F("'"));
        Adafruit_GFX &canvas = services.getCanvas();
        Adafruit_SharpMem &display = services.getDisplay();

        display.clearDisplay();

        canvas.setCursor(0, 0);
        canvas.setTextColor(COLOR_BLACK);
        canvas.setTextSize(2);
        canvas.print(message);

        if (cur == 0 && message[cur] == '\0') {
            setLeftNavigationLabel("Back");
        } else {
            setLeftNavigationLabel("Delete");
        }
        setRightNavigationLabel("Send");

        display.refresh();
    }

    /**
     * Converts sequence of keypad presses into text. Will blindly attempt to
     * access charset indices that overflow. Is time-sensitive: a pause between
     * presses of the same key will not cycle through characters. It will advance
     * the cursor and begin inputting again. Ensure that you do not exceed 11
     * or you'll crash. Guarding would waste an extra CPU instruction.
     *
     * Examples:
     *   2, 2 => "b"
     *   2, pause, 2 => "aa"
     *   3, 2, 3 => "dad"
     */
    void ComposeMessage::handleTextEntry(uint8_t charSetIdx) {
        unsigned long thisInputAt = millis();
        const CharSet charSet = KEY_TO_CHARS[charSetIdx];

        if (
            (thisInputAt - lastInputAt) < INPUT_CYCLE_TIMEOUT &&
                charSetIdx == lastCharSet
        ) {
            curChar = (curChar + 1) % charSet.length;
        } else if (message[cur] != '\0' && cur < MESSAGE_LENGTH) {
            curChar = 1;
            ++cur;
        }

        message[cur] = charSet.unmodified[curChar];

        lastCharSet = charSetIdx;
        lastInputAt = thisInputAt;
        draw();
    }

    void ComposeMessage::reset() {
        memset(number, '\0', sizeof(number));
        memset(message, '\0', sizeof(message));
        cur = 0;
        curChar = 1;
        lastCharSet = NO_CHAR_SET;
    }

    void ComposeMessage::sendMessage() {
        Adafruit_GFX &canvas = services.getCanvas();
        Adafruit_SharpMem &display = services.getDisplay();

        display.clearDisplay();

        canvas.setCursor(0, 0);
        canvas.setTextSize(3);
        canvas.print("Sending...");

        display.refresh();

        if (services.getFona().sendSMS(number, message)) {
            display.clearDisplay();
            canvas.setCursor(0, 0);
            canvas.print("Message sent.");
            display.refresh();
            delay(2500);
            reset();
            navigator.popController();
        } else {
            display.clearDisplay();
            canvas.setCursor(0, 0);
            canvas.print("Couldn't send.\nTry again");
            display.refresh();
            delay(2500);
            draw();
        }
    }
}
