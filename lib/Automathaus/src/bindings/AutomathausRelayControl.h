#ifndef AUTOMATHAUSWEBBINDRELAYCONTROL_H
#define AUTOMATHAUSWEBBINDRELAYCONTROL_H

#include "Automathaus.h"
#include "AutomathausWebServer.h"

class AutomathausRelayControl : public AutomathausWebBindings {
   public:
    void begin();
    //pin is the pin number, state is the state of the relay
    static int relayControl(int pin, bool state);
};

#endif  // AUTOMATHAUSWEBBINDRELAYCONTROL_H
