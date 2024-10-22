#include "Automathaus.h"
#include "bindings/mainBind.h"

AsyncWebServer server(80);
AutomathausCryptoRSAMbed automathausCrypto;
AutomathausKVSEspPreferences automathausPreferences;
AutomathausESPWifiNetworking automathausWifiNetworking;
AutomathausAsyncWebServer automathausWebServer(server, automathausWifiNetworking, automathausCrypto);
Automathaus automathaus(automathausWifiNetworking, automathausWebServer, automathausPreferences);

//implement main binding
void AutomathausWebBindMain::testMainBinding() {
    Serial.println("Test main binding executed");
}

void setup() {
    automathaus.start();
}

void loop() {
    automathaus.housekeeping();
}