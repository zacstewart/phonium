#ifndef COMPOSE_MESSAGE
#define COMPOSE_MESSAGE 4

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class ComposeMessage : public Controller {
  Navigator *navigator;
  Adafruit_SharpMem *display;
  Keypad *keypad;
  Adafruit_FONA *fona;
  char lastKey;
  uint8_t lastCharSet;
  unsigned long lastInputAt;
  uint8_t curChar;
  char number[NUMBER_LENGTH];
  char message[MESSAGE_LENGTH];
  uint8_t cur;

  public:
    ComposeMessage(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
    void begin();
    void update();

    void setNumber(char *);

  private:
    void backspace();
    void draw();
    void receiveInput(uint8_t);
    void reset();
    void sendMessage();
};

#endif
