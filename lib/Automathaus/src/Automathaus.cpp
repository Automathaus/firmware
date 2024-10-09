#include "Automathaus.h"
#include "AutomathausLogo.h"

Automathaus::Automathaus(AutomathausNetworking *networking, AutomathausWebServer *webServer) : networking(networking), webServer(webServer) {}

Automathaus::~Automathaus() {}

void Automathaus::start(int serialBaudrate){
    Serial.begin(serialBaudrate);
    Serial.println("======================================");
    Serial.println("     Automathaus - version 0.0.1");
    Serial.println("======================================");
    Serial.println(AUTOMATHAUS_LOGO);

    state = NODE_SETUP;

    networking->connectToNetwork();
    if (networking->getConnectionStatus() == WiFi_CONNECTED) {
        webServer->setWebInterface(state);
        webServer->onNotFound();
        webServer->begin();
    } else {
        // state = NODE_ERROR;
        Serial.println("Automathaus Error");
    }

    Serial.println("Automathaus started");
}

AutomathausState Automathaus::getState(){
    return state;
}