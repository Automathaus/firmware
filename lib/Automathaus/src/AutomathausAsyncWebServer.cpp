#include "AutomathausAsyncWebServer.h"

AutomathausAsyncWebServer::~AutomathausAsyncWebServer() {
    // Implementazione del distruttore, se necessario
}

void AutomathausAsyncWebServer::setWebInterface(const char *webPage){
    server->on("/", HTTP_GET, [webPage](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", webPage);
    });   
}

void AutomathausAsyncWebServer::onNotFound(){
    server->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "404 - Not found");
    });
}

void AutomathausAsyncWebServer::begin(){
    server->begin();
}