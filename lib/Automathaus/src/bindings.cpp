#include <ArduinoJson.h>
#include "AutomathausAsyncWebServer.h"
#include "AutomathausWebBindTest.h"

void AutomathausAsyncWebServer::setBindings() {
    _server.on("/bindings/AutomathausWebBindTest/testBinding", HTTP_POST,
               [](AsyncWebServerRequest *request) {
                   AutomathausWebBindTest::testBinding();
                   request->send(200, "text/plain", "{\"returnValue\": null}");
               });

    _server.on("/bindings/AutomathausWebBindTest/addInt", HTTP_POST,[](AsyncWebServerRequest *request) { 
        // Allocate the JSON document
        JsonDocument doc;

        // Parse the JSON body
        DeserializationError error = deserializeJson(doc, request->_tempObject);
        if (error) {
            request->send(400, "application/json", "{\"returnValue\": \"Invalid JSON\"}");
            return;
        }

        // Controlla se le chiavi sono presenti e accedi ai dati JSON analizzati
        int v1 = 0;
        int v2 = 0;

        if (doc["a"].is<int>()) {
            v1 = doc["a"].as<int>();
        }
        if (doc["b"].is<int>()) {
            v2 = doc["b"].as<int>();
        }
        
        // Chiama la funzione addInt
        int risultato = AutomathausWebBindTest::addInt(v1, v2);
        
        // Prepara la risposta JSON
        std::string risposta = "{\"returnValue\": " + std::to_string(risultato) + "}";
        
        // Invia la risposta
        request->send(200, "application/json", risposta.c_str());
    },
    NULL,
    AutomathausWebBindings::handleBody);
}
