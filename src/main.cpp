#include "Automathaus.h"

#define WIFI_SSID "Automathaus"
#define WIFI_PASSWORD "AutomatPass2023"

AsyncWebServer server(80);
AutomathausCryptoRSAMbed automathausCrypto;
AutomathausAsyncWebServer automathausWebServer(server, automathausCrypto);
AutomathausESPWifiNetworking automathausWifiNetworking(WIFI_SSID, WIFI_PASSWORD);
Automathaus automathaus(automathausWifiNetworking, automathausWebServer);

void setup() {
    automathaus.start();

    Serial.println("IP Address:");
    Serial.println(automathausWifiNetworking.getIPAddress());
    Serial.println("MAC Address:");
    Serial.println(automathausWifiNetworking.getMACAddress());
}

void loop() {}