#include "string.h"

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

ComposeMessage::ComposeMessage(Navigator *navigator, Adafruit_SharpMem *display, Keypad *keypad, Adafruit_FONA *fona)
: navigator(navigator)
, display(display)
, keypad(keypad)
, fona(fona)
, lastKey(NO_KEY)
, lastCharSet(NO_CHAR_SET)
, lastInputAt(0)
, curChar(1)
, number("")
, message("")
, cur(0)
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
          if (cur > 0) {
            backspace();
          } else {
            navigator->popController();
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
  // TODO: put this in main once all controllers handle key events
  keypad->getKeys();
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
  display->clearDisplay();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextSize(2);
  display->print(message);
  display->refresh();
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
  }  else if (
    message[cur] != '\0' &&
    cur < MESSAGE_LENGTH
  ) {
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
  display->setCursor(0, 0);
  display->setTextSize(3);
  display->clearDisplay();
  display->print("Sending...");
  display->refresh();

  if (fona->sendSMS(number, message)) {
    display->setCursor(0, 0);
    display->clearDisplay();
    display->print("Message sent.");
    display->refresh();
    delay(2500);
    reset();
    navigator->popController();
  } else {
    display->setCursor(0, 0);
    display->clearDisplay();
    display->print("Couldn't send.\nTry again");
    display->refresh();
    delay(2500);
    draw();
  }
}
