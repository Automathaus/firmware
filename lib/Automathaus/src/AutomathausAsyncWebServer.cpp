#include "AutomathausAsyncWebServer.h"
#include "AutomathausESPWifiNetworking.h"

AutomathausAsyncWebServer::~AutomathausAsyncWebServer() {
    // Implementazione del distruttore, se necessario
}

void AutomathausAsyncWebServer::setWebInterface(const char *webPage){
    _server.on("/", HTTP_GET, [webPage](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", webPage);
    });

    _server.on("/getRoute", HTTP_GET, [this](AsyncWebServerRequest *request){
        request->send(200, "text/json", this->getMode() == WEB_SERVER_RESET_MODE ? "{\"route\":\"/reset\"}" : "{\"route\":\"/\"}");
    });
}

void AutomathausAsyncWebServer::setWifiScannerRoute(){
    _server.on("/wifiScan", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "application/json", AutomathausESPWifiNetworking::scanWifiNetworks().c_str());
    });
}

void AutomathausAsyncWebServer::onNotFound(){
    _server.onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "404 - Not found");
    });
}

void AutomathausAsyncWebServer::begin(){
    _server.begin();
}