#include "Services.h"

Services::Services(Messaging messaging):
    messaging(messaging)
{
}

Messaging *Services::getMessaging() {
    return &messaging;
}
