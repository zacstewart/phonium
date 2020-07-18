#ifndef SERVICES
#define SERVICES

#include "Messaging.h"

class Services {
    public:
        Services(Messaging);

        Messaging *getMessaging();

    private:
        Messaging messaging;
};

#endif
