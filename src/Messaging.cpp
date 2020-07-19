#include "Messaging.h"

Element::Element(SmsMessage *sms):
    value(sms),
    next(NULL)
{
}

List::List():
    head(NULL),
    length(0)
{
}

void List::pushLeft(SmsMessage *sms) {
    Element *el = new Element(sms);
    el->next = head;
    head = el;
    length++;
}

Messaging::Messaging(Adafruit_FONA &fona):
    messages(new List()),
    fona(fona)
{
}

void Messaging::loadMessages() {
    uint8_t num = numSms();
    uint16_t messageLen;

    for (uint8_t i = 0; i < num; i++) {
        SmsMessage *sms = new SmsMessage();
        sms->index = i + 1;

        sms->message = (char *) malloc(sizeof(char) * MESSAGE_LENGTH + 1);
        fona.readSMS(i + 1, sms->message, MESSAGE_LENGTH, &messageLen);
        sms->message[messageLen] = '\0';
        realloc(sms->message, sizeof(char) * messageLen);

        fona.getSMSSender(i + 1, sms->sender, NUMBER_LENGTH);

        messages->pushLeft(sms);
    }
}

int8_t Messaging::numSms() {
    return fona.getNumSMS();
}
