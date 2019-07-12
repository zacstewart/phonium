#ifndef MESSAGES
#define MESSAGES 5

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class Messages : public Controller {
  Navigator *navigator;
  Adafruit_SharpMem *display;
  Keypad *keypad;
  Adafruit_FONA *fona;
  int8_t numMessages;
  char **previews;
  uint8_t curMessage;

  public:
    Messages(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
    void begin();
    void handleKeyInput(KeyState state, KeypadEvent key);
    void update();

    void loadMessages();

  private:
    void draw();
    void cursorDown();
    void cursorUp();
};

#endif
