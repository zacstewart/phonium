#ifndef HOME
#define HOME 0

#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class Home : public Controller {
  Navigator *navigator;
  Adafruit_SharpMem *display;
  Keypad *keypad;
  Adafruit_FONA *fona;

  public:
    Home(Navigator *, Adafruit_SharpMem *, Keypad *, Adafruit_FONA *);
    void begin();
    void update();

  private:
    void startDialing(char);
};

#endif
