#ifndef HOME
#define HOME 0

#include <Adafruit_EPD.h>
#include <Adafruit_FONA.h>
#include <Keypad.h>

#include "Common.h"
#include "Navigator.h"
#include "Controller.h"

class Home : public Controller {
  Navigator *navigator;
  Adafruit_SSD1608 *display;
  Keypad *keypad;
  Adafruit_FONA *fona;

  public:
    Home(Navigator *, Adafruit_SSD1608 *, Keypad *, Adafruit_FONA *);
    void begin();
    void update();

  private:
    void startDialing(char);
};

#endif
