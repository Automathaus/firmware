#ifndef AUTOMATHAUSWEBRESET_H
#define AUTOMATHAUSWEBRESET_H

#include "Automathaus.h"
#include "AutomathausWebServer.h"

class AutomathausWebReset : public AutomathausWebBindings {
   public:
    static void testBinding() {
        Serial.println("Test binding executed");
    };

    static int addInt(int a, int b) {
        return a + b;
    };
};

#endif  // AUTOMATHAUSWEBRESET_H