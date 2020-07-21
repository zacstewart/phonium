#include <Adafruit_FONA.h>
#include <Adafruit_SharpMem.h>
#include <HardwareSerial.h>
#include <Keypad.h>

#include "Display.h"
#include "Messaging.h"
#include "Services.h"

#include "Common.h"
#include "Controller.h"
#include "Navigator.h"

#include "Controllers/Call.h"
#include "Controllers/ComposeMessage.h"
#include "Controllers/Dialer.h"
#include "Controllers/Home.h"
#include "Controllers/IncomingCall.h"
#include "Controllers/Menu.h"
#include "Controllers/Message.h"
#include "Controllers/Messages.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define SHARP_SCK  13
#define SHARP_MOSI 11
#define SHARP_SS   4
#define DISPLAY_ROTATION 3 // Headers to the left

#define FONA_RI  3
#define FONA_RST 2
#define FONA_BAUD_RATE 115200

static byte keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
static byte rowPins[KEYPAD_ROWS] = {18, 19, 20, 21};
static byte colPins[KEYPAD_COLS] = {17, 16, 15, 14};
static Keypad keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

static Adafruit_SharpMem displayDevice(SHARP_SCK, SHARP_MOSI, SHARP_SS, DISPLAY_HEIGHT, DISPLAY_WIDTH);

static Adafruit_FONA fona(FONA_RST);

/**
 * Services
 */
//TODO: Once switching to EPD, one of these will be the GFX canvas
static Display display(displayDevice, displayDevice);
static Messaging messaging(fona);
static Services services(fona, display, messaging);

/**
 * Controllers
 */
static Navigator navigator;
static Controllers::Call call(services, navigator);
static Controllers::ComposeMessage composeMessage(services, navigator);
static Controllers::Dialer dialer(services, navigator);
static Controllers::Home home(services, navigator);
static Controllers::IncomingCall incomingCall(services, navigator);
static Controllers::Menu menu(services, navigator);
static Controllers::Message message(services, navigator);
static Controllers::Messages messages(services, navigator);

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
    displayDevice.begin();
    displayDevice.setRotation(DISPLAY_ROTATION);

    Display &display = services.getDisplay();
    Adafruit_GFX &canvas = display.getCanvas();
    display.clear();
    canvas.setCursor(0, 0);
    canvas.setTextColor(COLOR_BLACK);
    canvas.setTextSize(2);
    canvas.print("Starting");
    display.refresh();

    Serial.println(F("Starting cellular"));
    Serial1.begin(FONA_BAUD_RATE);
    if (!fona.begin(Serial1)) {
        Serial.println(F("Couldn't find FONA"));
    }
    fona.callerIdNotification(true, digitalPinToInterrupt(FONA_RI));
    fona.setAudio(FONA_EXTAUDIO);
    fona.setMicVolume(FONA_EXTAUDIO, 10);

    services.getMessaging().loadMessages();

    navigator.setController(CALL, &call);
    navigator.setController(COMPOSE_MESSAGE, &composeMessage);
    navigator.setController(DIALER, &dialer);
    navigator.setController(HOME, &home);
    navigator.setController(INCOMING_CALL, &incomingCall);
    navigator.setController(MENU, &menu);
    navigator.setController(MESSAGE, &message);
    navigator.setController(MESSAGES, &messages);

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
