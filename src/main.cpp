#include <Arduino.h>
#include <DNSServer.h>
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "Automathaus.h"
#include "AutomathausESPWifiNetworking.h"

AsyncWebServer server(80);
AutomathausAsyncWebServer automathausWebServer(&server);
Automathaus automathaus(&automathausWebServer);
AutomathausESPWifiNetworking automathausWifiNetworking("Automathaus", "AutomatPass2023");

// const char* ssid = "H3140-74454476";
// const char* password = "Zk7FZEUSuz";

void setup() {
    Serial.begin(115200);
    automathausWifiNetworking.connectToNetwork();
    
    //print the connection status
    Serial.println("Connection Status:");
    Serial.println(automathausWifiNetworking.getConnectionStatus());

    Serial.println("IP Address:");
    Serial.println(automathausWifiNetworking.getIPAddress());
    Serial.println("MAC Address:");
    Serial.println(automathausWifiNetworking.getMACAddress());


    automathaus.start();
}

void loop() {}