#ifndef COMPOSE_MESSAGE
#define COMPOSE_MESSAGE 3

#include "Adafruit_EPD.h"
#include <Adafruit_FONA.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class ComposeMessage : public Controller {
  Navigator *navigator;
  Adafruit_SSD1608 *display;
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
    ComposeMessage(Navigator *, Adafruit_SSD1608 *, Keypad *, Adafruit_FONA *);
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
