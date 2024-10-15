#ifndef AUTOMATHAUSWEBBINDTEST_H
#define AUTOMATHAUSWEBBINDTEST_H

#include "Automathaus.h"
#include "AutomathausWebServer.h"

class AutomathausWebBindTest : public AutomathausWebBindings {
   public:
    static void testBinding() {
        Serial.println("Test binding executed");
    };

    static int addInt(int a, int b) {
        return a + b;
    };

    static int multiplyInt(int a, int b) {
        return a * b;
    };
};

#endif  // AUTOMATHAUSWEBBINDTEST_H