#include "Automathaus.h"
#include "AutomathausLogo.h"

Automathaus::Automathaus(AutomathausNetworking &networking, AutomathausWebServer &webServer) : _networking(networking), _webServer(webServer) {
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

    _state = TRY_CONNECT;

    _networking.connectToNetwork();
    if (_networking.getConnectionStatus() == NET_CONNECTED) {
        _webServer.setMode(WEB_SERVER_NORMAL_MODE);
        _webServer.setWifiScannerRoute(); // ONLY FOR TESTING
        _webServer.setWebInterface(INDEX_HTML);
        _webServer.onNotFound();
        _webServer.begin();
        _state = CONNECTED;
    } else {
        // state = NODE_ERROR;
        Serial.println("Automathaus Error");
    }

    Serial.println("Automathaus started");
}

AutomathausState Automathaus::getState(){
    return _state;
}