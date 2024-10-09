#include <Arduino.h>
#include <DNSServer.h>
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
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