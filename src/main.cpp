#include <Adafruit_FONA.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include <HardwareSerial.h>
#include <Keypad.h>

#include "Messaging.h"
#include "Services.h"

#include "Common.h"
#include "Controller.h"
#include "Navigator.h"

#include "Call.h"
#include "ComposeMessage.h"
#include "Dialer.h"
#include "Home.h"
#include "IncomingCall.h"
#include "Message.h"
#include "Messages.h"
#include "Menu.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define SHARP_SCK  13
#define SHARP_MOSI 11
#define SHARP_SS   4
#define DISPLAY_ROTATION 3 // Headers to the left

#define FONA_RI  3
#define FONA_RST 2
#define FONA_BAUD_RATE 115200

byte keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[KEYPAD_ROWS] = {18, 19, 20, 21};
byte colPins[KEYPAD_COLS] = {17, 16, 15, 14};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, DISPLAY_HEIGHT, DISPLAY_WIDTH);

HardwareSerial *fonaSerial = &Serial1;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

/**
 * Services
 */
Messaging messaging = Messaging(&fona);
Services services = Services(messaging);

/**
 * Controllers
 */
Navigator navigator = Navigator();

Call call = Call(&services, &navigator, &display, &keypad, &fona);
ComposeMessage composeMessage = ComposeMessage(&services, &navigator, &display, &keypad, &fona);
Dialer dialer = Dialer(&services, &navigator, &display, &keypad, &fona);
Home home = Home(&services, &navigator, &display, &keypad, &fona);
IncomingCall incomingCall = IncomingCall(&services, &navigator, &display, &keypad, &fona);
Message message = Message(&services, &navigator, &display, &keypad, &fona);
Messages messages = Messages(&services, &navigator, &display, &keypad, &fona);
Menu menu = Menu(&services, &navigator, &display, &keypad, &fona);

#ifdef USING_MAKEFILE
extern "C" int main(void) {
    setup();
    while (1) {
        loop();
        yield();
    }
}
#endif

void handleKeyInput(KeypadEvent key) {
    navigator.currentController()->handleKeyInput(keypad.getState(), key);
}

void setup() {
#ifdef DEBUG
    while (!Serial);
#endif

    Serial.begin(115200);

#ifdef DEBUG
    Serial.print("Build date: ");
    Serial.println(BUILD_DATE);
#endif

    Serial.println(F("Phonium starting"));

    keypad.addEventListener(handleKeyInput);

    Serial.println(F("Starting display"));
    display.begin();
    display.setRotation(DISPLAY_ROTATION);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(COLOR_BLACK);
    display.setTextSize(2);
    display.print("Starting");
    display.refresh();

    Serial.println(F("Starting cellular"));
    fonaSerial->begin(FONA_BAUD_RATE);
    if (!fona.begin(*fonaSerial)) {
        Serial.println(F("Couldn't find FONA"));
    }
    fona.callerIdNotification(true, digitalPinToInterrupt(FONA_RI));
    fona.setAudio(FONA_EXTAUDIO);
    fona.setMicVolume(FONA_EXTAUDIO, 10);

    services.getMessaging()->loadMessages();

    // TODO: replace this with a constructor of some kind
    messages.setServices(&services);

    navigator.setController(CALL, &call);
    navigator.setController(COMPOSE_MESSAGE, &composeMessage);
    navigator.setController(DIALER, &dialer);
    navigator.setController(INCOMING_CALL, &incomingCall);
    navigator.setController(HOME, &home);
    navigator.setController(MESSAGES, &messages);
    navigator.setController(MESSAGE, &message);
    navigator.setController(MENU, &menu);

    Serial.println(F("Phonium ready"));
    navigator.replaceController(HOME);
}

void loop() {
    if (fona.incomingCallNumber(incomingCall.number)) {
        navigator.pushController(INCOMING_CALL);
    }
    keypad.getKeys();
    navigator.currentController()->update();
}
