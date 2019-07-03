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

void ComposeMessage::update() {
  char key = keypad->getKey();

  if (
    key == NO_KEY && // Not pressing a key
    message[cur] != '\0' && // Not already at the end
    (millis() - lastInputAt) > INPUT_CYCLE_TIMEOUT // Timeout has elapsed
  ) {
    lastCharSet = NO_CHAR_SET;
    curChar = 1;
    ++cur;
  }

  if (key == lastKey) {
    return;
  }
  lastKey = key;

  switch (key) {
    case NO_KEY:
      break;
    case 'A':
      backspace();
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
      receiveInput((uint8_t) key - '0');
      break;
    case '*':
      receiveInput(10);
      break;
    case '#':
      receiveInput(11);
      break;
    default:
      break;
  }
  Serial.print("Message: '"); Serial.print(message); Serial.println("'");
}

void ComposeMessage::setNumber(char *num) {
  memcpy(number, num, sizeof(number));
}

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
  display->clearDisplay();
  display->setCursor(0, 0);
  display->setTextColor(COLOR_BLACK);
  display->setTextSize(2);
  display->print(message);
  display->refresh();
}

void ComposeMessage::receiveInput(uint8_t charSetIdx) {
  const CharSet charSet = KEY_TO_CHARS[charSetIdx];

  if (charSetIdx == lastCharSet) {
    curChar = (curChar + 1) % charSet.length;
  }  else if (
    charSetIdx >= 0 &&
    charSetIdx < 12 &&
    message[cur] != '\0' &&
    cur < MESSAGE_LENGTH
  ) {
    curChar = 1;
    ++cur;
  }

  message[cur] = charSet.unmodified[curChar];

  lastInputAt = millis();
  lastCharSet = charSetIdx;
  draw();
}

void ComposeMessage::reset() {
  memset(number, '\0', sizeof(number));
  curChar = 1;
  cur = 0;
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
