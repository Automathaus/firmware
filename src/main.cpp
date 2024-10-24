#include "Automathaus.h"
#include "bindings/AutomathausRelayControl.h"

AsyncWebServer server(80);
AutomathausCryptoRSAMbed automathausCrypto;
AutomathausKVSEspPreferences automathausPreferences;
AutomathausESPWifiNetworking automathausWifiNetworking;
AutomathausAsyncWebServer automathausWebServer(server, automathausWifiNetworking, automathausCrypto);
Automathaus automathaus(automathausWifiNetworking, automathausWebServer, automathausPreferences);



AutomathausRelayControl automathausRelayControl;

void AutomathausRelayControl::begin() {
    int arr[8] = {4, 5, 6, 7, 15, 16, 17, 18};
    for (int i = 0; i < 8; i++) {
        pinMode(arr[i], OUTPUT);
        digitalWrite(arr[i], HIGH); // Ensure relay is off at startup
    }
}

//implement main binding
int AutomathausRelayControl::relayControl(int pin, bool state) {
    digitalWrite(pin, state ? LOW : HIGH);
    return 0;
}

void setup() {
    automathausRelayControl.begin();
    automathaus.start("controller");
}

void loop() {
    automathaus.housekeeping();
}