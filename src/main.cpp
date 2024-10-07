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
Automathaus automathaus(&automathausWebServer);

const char* ssid = "H3140-74454476";
const char* password = "Zk7FZEUSuz";

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());

    automathaus.start();
}

void loop() {}