#include "AutomathausWebBindTest.h"
#include <ArduinoJson.h>
#include "AutomathausAsyncWebServer.h"

void AutomathausAsyncWebServer::setGeneratedBindings() {

    // Void function case for AutomathausWebBindTest::testBinding
    _server.on("/bindings/AutomathausWebBindTest/testBinding", HTTP_POST, [](AsyncWebServerRequest *request) {
        AutomathausWebBindTest::testBinding();
        request->send(200, "text/plain", "{\"returnValue\": null}");
    },
    NULL,
    handleBody);

    // Function with return value case for AutomathausWebBindTest::addInt
    _server.on("/bindings/AutomathausWebBindTest/addInt", HTTP_POST, [](AsyncWebServerRequest *request) { 
        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, request->_tempObject);
        if (error) {
            Serial.println(error.c_str());
            request->send(400, "application/json", "{\"returnValue\": \"Invalid JSON\"}");
            return;
        }

        int v1 = 0;
        if (doc["a"].is<int>()) {
            v1 = doc["a"].as<int>();
        } else {
            request->send(400, "application/json", "{\"error\": \"Invalid or missing 'a' parameter\"}");
            return;
        }

        int v2 = 0;
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
    handleBody);

    // Function with return value case for AutomathausWebBindTest::multiplyInt
    _server.on("/bindings/AutomathausWebBindTest/multiplyInt", HTTP_POST, [](AsyncWebServerRequest *request) { 
        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, request->_tempObject);
        if (error) {
            Serial.println(error.c_str());
            request->send(400, "application/json", "{\"returnValue\": \"Invalid JSON\"}");
            return;
        }

        int v1 = 0;
        if (doc["a"].is<int>()) {
            v1 = doc["a"].as<int>();
        } else {
            request->send(400, "application/json", "{\"error\": \"Invalid or missing 'a' parameter\"}");
            return;
        }

        int v2 = 0;
        if (doc["b"].is<int>()) {
            v2 = doc["b"].as<int>();
        } else {
            request->send(400, "application/json", "{\"error\": \"Invalid or missing 'b' parameter\"}");
            return;
        }

        auto returnValue = AutomathausWebBindTest::multiplyInt(v1, v2);

        std::string response = "{\"returnValue\": " + std::to_string(returnValue) + "}";
        request->send(200, "application/json", response.c_str());
    },
    NULL,
    handleBody);

    // Function with return value case for AutomathausWebBindTest::getString
    _server.on("/bindings/AutomathausWebBindTest/getString", HTTP_POST, [](AsyncWebServerRequest *request) { 
        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, request->_tempObject);
        if (error) {
            Serial.println(error.c_str());
            request->send(400, "application/json", "{\"returnValue\": \"Invalid JSON\"}");
            return;
        }

        auto returnValue = AutomathausWebBindTest::getString();

        std::string response = "{\"returnValue\": \"" + returnValue + "\"}";
        request->send(200, "application/json", response.c_str());
    },
    NULL,
    handleBody);

}
