#include "AutomathausAsyncWebServer.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "AutomathausWebReset.h"

void AutomathausAsyncWebServer::setBindings() {
    _server.on("/bindings/AutomathausWebReset/testBinding", HTTP_POST, [](AsyncWebServerRequest *request) {
        AutomathausWebReset::testBinding();
        request->send(200, "text/plain", "{\"returnValue\": null}");
    });

    // Define the JSON endpoint
    AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/bindings/AutomathausWebReset/addInt",
        [](AsyncWebServerRequest *request, JsonVariant &json) {
            JsonObject jsonObj = json.as<JsonObject>();
            int v1 = 0;
            int v2 = 0;

            if (jsonObj["a"].is<int>()) {
                v1 = jsonObj["a"].as<int>();
            }

            if (jsonObj["b"].is<int>()) {
                v2 = jsonObj["b"].as<int>();
            }

            int returnValue = AutomathausWebReset::addInt(v1, v2);

            std::string response = "{\"returnValue\": " + std::to_string(returnValue) + "}";
            request->send(200, "application/json", response.c_str());
    });

    _server.addHandler(handler);
}