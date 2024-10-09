#include "Automathaus.h"
#include "AutomathausLogo.h"

Automathaus::Automathaus(AutomathausNetworking *networking, AutomathausWebServer *webServer) : _networking(networking), _webServer(webServer) {}

Automathaus::~Automathaus() {}

void Automathaus::start(int serialBaudrate){
    Serial.begin(serialBaudrate);
    Serial.println("===================================================");
    Serial.println("||            Automathaus - version 0.0.1        ||");
    Serial.println("===================================================");
    Serial.println(AUTOMATHAUS_LOGO);

    _state = NODE_SETUP;

    _networking->connectToNetwork();
    if (_networking->getConnectionStatus() == NET_CONNECTED) {
        _webServer->setWebInterface(INDEX_HTML);
        _webServer->onNotFound();
        _webServer->begin();
    } else {
        // state = NODE_ERROR;
        Serial.println("Automathaus Error");
    }

    Serial.println("Automathaus started");
}

AutomathausState Automathaus::getState(){
    return _state;
}