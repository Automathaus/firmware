#include "Automathaus.h"

AsyncWebServer server(80);
AutomathausAsyncWebServer automathausWebServer(&server);
AutomathausESPWifiNetworking automathausWifiNetworking("Automathaus", "AutomatPass2023");
Automathaus automathaus(&automathausWifiNetworking, &automathausWebServer);

// const char* ssid = "H3140-74454476";
// const char* password = "Zk7FZEUSuz";

void setup() {
    automathaus.start();

    Serial.println("IP Address:");
    Serial.println(automathausWifiNetworking.getIPAddress());
    Serial.println("MAC Address:");
    Serial.println(automathausWifiNetworking.getMACAddress());
}

void loop() {}