#ifndef MESSAGING
#define MESSAGING

#include <Adafruit_FONA.h>

#include "Common.h"

typedef struct SmsMessage {
    uint8_t index;
    char *message;
    // +1 for null terminator
    char sender[NUMBER_LENGTH + 1];
} SmsMessage;

class Element {
    public:
        SmsMessage *value;
        Element *next;

        Element(SmsMessage *);
};

class List {
    public:
        Element *head;
        size_t length;

        List();

        void pushLeft(SmsMessage *);
};

/**
 * Service to encapsulate SMS messaging
 */
class Messaging {
    public:
        List *messages;

        // TODO: this should take ownership of FONA and loan it out
        Messaging(Adafruit_FONA *);

        /**
         * Loads all messages out of the SIM into memory
         */
        void loadMessages();

    private:
        Adafruit_FONA *fona;

        /**
         * Reads SMS message from the SIM and loads it onto the provided struct
         */
        void readSms(uint8_t, SmsMessage *);

        int8_t numSms();
};

#endif
