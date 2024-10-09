#include "AutomathausAsyncWebServer.h"
#include "AutomathausWebServer.h"
#include "webgui.h"

AutomathausAsyncWebServer::~AutomathausAsyncWebServer() {
    // Implementazione del distruttore, se necessario
}

void AutomathausAsyncWebServer::setWebInterface(AutomathausState state){
    switch (state){
        case NODE_SETUP:
            server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
                request->send_P(200, "text/html", INDEX_HTML);
            });
        break;
        // Aggiungi altri casi se necessario
    }
}

void AutomathausAsyncWebServer::onNotFound(){
    server->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "404 - Not found");
    });
}

void AutomathausAsyncWebServer::begin(){
    server->begin();
}