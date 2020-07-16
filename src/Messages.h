#ifndef MESSAGES
#define MESSAGES 5

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"
#include "Messaging.h"

class Messages : public Controller {
  using Controller::Controller;

  Messaging *messaging;
  int8_t numMessages;
  uint8_t curMessage;

  public:
    Messages(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
    /**
     * TODO: replace this with constructor
     */
    void setMessaging(Messaging *);
    void begin();
    void handleKeyInput(KeyState state, KeypadEvent key);
    void update();

  private:
    void draw();
    void cursorDown();
    void cursorUp();
};

#endif
