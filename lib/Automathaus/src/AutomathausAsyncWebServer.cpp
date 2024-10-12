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
        char route[128];

        switch (this->getMode()) {
            case WEB_SERVER_RESET_MODE:
                snprintf(route, sizeof(route), JSON_TEMPLATE, Routes::RESET);
                break;
            case WEB_SERVER_NORMAL_MODE:
                snprintf(route, sizeof(route), JSON_TEMPLATE, Routes::ROOT);
                break;
        }
        request->send(200, "text/json", route);
    });

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
    (void)AutomathausESPWifiNetworking::scanWifiNetworks();
    _server.begin();
}