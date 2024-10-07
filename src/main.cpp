#include <Arduino.h>
#include <DNSServer.h>
#ifdef ESP32
#include <AsyncTCP.h>
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "webgui.h"
#include "Automathaus.h"

AsyncWebServer server(80);
AutomathausAsyncWebServer automathausWebServer(&server);
Automathaus automathaus(&automathausWebServer);

const char* ssid = "H3140-74454476";
const char* password = "Zk7FZEUSuz";

// void notFound(AsyncWebServerRequest *request) {
//     request->send(404, "text/plain", "Not found");
// }

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

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //     request->send_P(200, "text/html", INDEX_HTML);
    // });

    // server.onNotFound(notFound);
    // server.begin();
}

void loop() {}