#ifndef MESSAGE
#define MESSAGE 6

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

typedef struct SmsMessage {
  uint8_t index;
  char message[MESSAGE_LENGTH + 1];
  // +1 for null terminator
  char sender[NUMBER_LENGTH + 1];
} SmsMessage;

class Message : public Controller {
  Navigator *navigator;
  Adafruit_SharpMem *display;
  Keypad *keypad;
  Adafruit_FONA *fona;
  SmsMessage message;

  public:
    Message(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
    void begin();
    void update();

    void setMessage(uint8_t);

  private:
};

#endif
