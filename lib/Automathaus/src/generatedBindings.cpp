#include <ArduinoJson.h>
#include "AutomathausAsyncWebServer.h"
#include "AutomathausWebBindTest.h"

void AutomathausAsyncWebServer::setGeneratedBindings() {

    //Void funcion case
    _server.on("/bindings/AutomathausWebBindTest/testBinding", HTTP_POST, [](AsyncWebServerRequest *request) {
        AutomathausWebBindTest::testBinding();
        request->send(200, "text/plain", "{\"returnValue\": null}");
    });

    //Function with return value case
    _server.on("/bindings/AutomathausWebBindTest/addInt", HTTP_POST, [](AsyncWebServerRequest *request) { 
        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, request->_tempObject);
        if (error) {
            Serial.println(error.c_str());
            request->send(400, "application/json", "{\"returnValue\": \"Invalid JSON\"}");
            return;
        }

        int v1 = 0;
        int v2 = 0;

        if (doc["a"].is<int>()) {
            v1 = doc["a"].as<int>();
        } else {
            request->send(400, "application/json", "{\"error\": \"Invalid or missing 'a' parameter\"}");
            return;
        }

        if (doc["b"].is<int>()) {
            v2 = doc["b"].as<int>();
        } else {
            request->send(400, "application/json", "{\"error\": \"Invalid or missing 'b' parameter\"}");
            return;
        }

        auto returnValue = AutomathausWebBindTest::addInt(v1, v2);
        
        std::string response = "{\"returnValue\": " + std::to_string(returnValue) + "}";
        request->send(200, "application/json", response.c_str());
    },
    NULL,
    AutomathausWebBindings::handleBody);
}
