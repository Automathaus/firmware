#include "Automathaus.h"
#include "AutomathausLogo.h"

Automathaus::Automathaus(AutomathausNetworking &networking, AutomathausWebServer &webServer, AutomathausKeyValueStore &kvStore) : _networking(networking), _webServer(webServer), _kvStore(kvStore) {
    _state = START;
}

Automathaus::~Automathaus() {}

void Automathaus::start(const char* nodeType, int serialBaudrate){
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

    _kvStore.setNodeType(nodeType);

    if (_kvStore.getNodeName().length() == 0) {
        char nodeName[20] = {0};
        snprintf(nodeName, sizeof(nodeName), "%s%d", AutomathausNetworking::HOSTNAME, random(0, 9999));
        _kvStore.setNodeName(nodeName);
    }

    ConnectionStatus connectionStatus = NET_SETUP;

    if (_kvStore.getWifiSSID().length() > 0 && _kvStore.getWifiPassword().length() > 7) {
        _networking.setCredentials(_kvStore.getWifiSSID().c_str(), _kvStore.getWifiPassword().c_str());
        connectionStatus = _networking.connectToNetwork();
    }

    _state = TRY_CONNECT;


    switch (connectionStatus) {
        case NET_CONNECTED:
            _state = CONNECTED;
            Serial.println("Connected to network");
            _networking.findServerIPAddress();
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

    #ifdef LED_BUILTIN
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);
    #endif
}

AutomathausState Automathaus::getState(){
    return _state;
}

void Automathaus::housekeeping(){
    if(_state == NODE_SETUP){
        _networking.housekeeping();
    }
}
