#include "Automathaus.h"

#define WIFI_SSID "AutomathausDev"
#define WIFI_PASSWORD "AutomatPass1234"

AsyncWebServer server(80);
AutomathausCryptoRSAMbed automathausCrypto;
AutomathausKVSEspPreferences automathausPreferences;
AutomathausESPWifiNetworking automathausWifiNetworking;
AutomathausAsyncWebServer automathausWebServer(server, automathausWifiNetworking, automathausCrypto);
Automathaus automathaus(automathausWifiNetworking, automathausWebServer, automathausPreferences);

void setup() {
    automathaus.start();
    // automathausPreferences.begin();
    // automathausPreferences.clearAll();

    // automathausPreferences.setNodeName("AutomathausDev");
    // Serial.println("Node Name:");
    // Serial.println(automathausPreferences.getNodeName());


    // Serial.println("IP Address:");
    // Serial.println(automathausWifiNetworking.getIPAddress());
    // Serial.println("MAC Address:");
    // Serial.println(automathausWifiNetworking.getMACAddress());
}

void loop() {
    automathaus.housekeeping();
}