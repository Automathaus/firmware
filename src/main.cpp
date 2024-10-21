#include "Automathaus.h"

#define WIFI_SSID "AutomathausDev"
#define WIFI_PASSWORD "AutomatPass1234"

AsyncWebServer server(80);
AutomathausCryptoRSAMbed automathausCrypto;
AutomathausKVSEspPreferences automathausKVSEspPreferences;
AutomathausESPWifiNetworking automathausWifiNetworking(WIFI_SSID, WIFI_PASSWORD);
AutomathausAsyncWebServer automathausWebServer(server, automathausWifiNetworking, automathausCrypto);
Automathaus automathaus(automathausWifiNetworking, automathausWebServer);

void setup() {
    automathaus.start();

    // automathausKVSEspPreferences.begin();
    // automathausKVSEspPreferences.clearAll();
    // automathausKVSEspPreferences.setNodeName("AutomathausDev");
    // Serial.println("Node Name:");
    // Serial.println(automathausKVSEspPreferences.getNodeName());


    // Serial.println("IP Address:");
    // Serial.println(automathausWifiNetworking.getIPAddress());
    // Serial.println("MAC Address:");
    // Serial.println(automathausWifiNetworking.getMACAddress());
}

void loop() {
    automathaus.housekeeping();
}