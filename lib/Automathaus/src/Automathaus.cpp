#include "Automathaus.h"
#include "AutomathausLogo.h"

Automathaus::Automathaus(AutomathausNetworking &networking, AutomathausWebServer &webServer, AutomathausKeyValueStore &kvStore) : _networking(networking), _webServer(webServer), _kvStore(kvStore) {
    _state = START;
}

Automathaus::~Automathaus() {}

void Automathaus::start(int serialBaudrate){
    if (!Serial) {
        Serial.begin(serialBaudrate);
    }


    Serial.println("===================================================");
    Serial.println("||            Automathaus - version 0.0.1        ||");
    Serial.println("===================================================");
    Serial.println(AUTOMATHAUS_LOGO);

    if (!_kvStore.begin()) {
        Serial.println("Failed to initialize key-value store");
        return;
    }

    _state = TRY_CONNECT;

    switch (_networking.connectToNetwork()) {
        case NET_CONNECTED:
            _state = CONNECTED;
            Serial.println("Connected to network");
            _webServer.setMode(WEB_SERVER_NORMAL_MODE);
            break;
        case NET_SETUP:
            Serial.println("Starting setup mode");
            _webServer.setMode(WEB_SERVER_SETUP_MODE);
            _networking.startSetupMode();
            _state = NODE_SETUP;
            break;
    }

    Serial.println("Automathaus started");
    _webServer.setWebInterface(INDEX_HTML);
    _webServer.begin(_kvStore);
}

AutomathausState Automathaus::getState(){
    return _state;
}

void Automathaus::housekeeping(){
    if(_state == NODE_SETUP){
        _networking.housekeeping();
    }
}