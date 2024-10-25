#include "AutomathausESPWifiNetworking.h"


AutomathausESPWifiNetworking::AutomathausESPWifiNetworking(const char* ssid, const char* password) {
    setCredentials(ssid, password);
}

AutomathausESPWifiNetworking::AutomathausESPWifiNetworking() {
    // Default constructor
}

AutomathausESPWifiNetworking::~AutomathausESPWifiNetworking() {
    // Destructor
}


// Set the credentials for the WiFi network
void AutomathausESPWifiNetworking::setCredentials(const char* ssid, const char* password) {
    if (ssid == NULL || password == NULL) {
        _connectionStatus = NET_FAILED;
        return;
    }

    strncpy(_ssid, ssid, 32);
    strncpy(_password, password, 64);
    _ssid[32] = '\0';
    _password[64] = '\0';
}

// Connect to the WiFi network
ConnectionStatus AutomathausESPWifiNetworking::connectToNetwork() {
    // Disconnect if connected
    if(WiFi.status() == WL_CONNECTED) {
        WiFi.disconnect(true);  // Disconnect and clear credentials
    }
    
    // Stop AP if active
    if(WiFi.getMode() & WIFI_MODE_AP) {
        WiFi.softAPdisconnect(true);  // Disconnect AP and clear AP config
    }
    delay(100); 

    if (_ssid == NULL || _password == NULL) {
        _connectionStatus = NET_FAILED;
        return _connectionStatus;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);

    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi connection failed!");
        WiFi.disconnect();
        _connectionStatus = NET_SETUP;
        return _connectionStatus;
    }

    _connectionStatus = NET_CONNECTED;
    Serial.println("Connected to WiFi");
    Serial.println("IP address: " + WiFi.localIP().toString());
    Serial.println("MAC address: " + WiFi.macAddress());
    strncpy(_IPAddress, WiFi.localIP().toString().c_str(), 16);
    strncpy(_MACAddress, WiFi.macAddress().c_str(), 18);
    return _connectionStatus;
}


std::string AutomathausESPWifiNetworking::scanWifiNetworks(){
    std::string json = "[";
    int n = WiFi.scanComplete();
    if (n == -2) {
        WiFi.scanNetworks(true);
    } else if (n) {
        for (int i = 0; i < n; ++i) {
            if (i) json += ",";
            json += "{";
            int rssi = WiFi.RSSI(i);
            int signal_strength;
            if (rssi >= -50) {
                signal_strength = 4;
            } else if (rssi >= -60) {
                signal_strength = 3;
            } else if (rssi >= -70) {
                signal_strength = 2;
            } else if (rssi >= -80) {
                signal_strength = 1;
            } else {
                signal_strength = 0;
            }

            json += "\"signalStrength\":" + std::to_string(signal_strength);
            json += ",\"ssid\":\"" + std::string(WiFi.SSID(i).c_str()) + "\"";
            json += ",\"bssid\":\"" + std::string(WiFi.BSSIDstr(i).c_str()) + "\"";
            json += ",\"channel\":" + std::to_string(WiFi.channel(i));
            json += ",\"secure\":\"";

            switch (WiFi.encryptionType(i)) {
                case WIFI_AUTH_OPEN:
                    json += "Open";
                    break;
                case WIFI_AUTH_WEP:
                    json += "WEP";
                    break;
                case WIFI_AUTH_WPA_PSK:
                    json += "WPA-PSK";
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    json += "WPA2-PSK";
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    json += "WPA/WPA2-PSK";
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    json += "WPA2-Enterprise";
                    break;
                default:
                    json += "Sconosciuto";
                    break;
            }
            
            json += "\"";
            json += "}";
        }
        WiFi.scanDelete();
        if (WiFi.scanComplete() == -2) {
            WiFi.scanNetworks(true);
        }
    }
    json += "]";

    Serial.println(json.c_str());
    return json;
}



// Get the IP address of the device
char* AutomathausESPWifiNetworking::getIPAddress() {
    return _IPAddress;
}

// Get the MAC address of the device
char* AutomathausESPWifiNetworking::getMACAddress() {
    return _MACAddress;
}

void AutomathausESPWifiNetworking::disconnectFromNetwork() {
    WiFi.disconnect();
    _connectionStatus = NET_DISCONNECTED;
}

// Get the connection status of the device
ConnectionStatus AutomathausESPWifiNetworking::getConnectionStatus() {
    return _connectionStatus;
}

void AutomathausESPWifiNetworking::startSetupMode() {
    _connectionStatus = NET_SETUP;
    randomSeed(millis());
    String randomStr = "";
    // for (int i = 0; i < 5; i++) {
    //     int randomNumber = random(0, 10); // Generate a random number between 0 and 9
    //     randomStr += String(randomNumber);
    // }

    Serial.println("Starting configuration Access point");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(HOSTNAME + randomStr, AP_PASSWORD);
    _dnsServer.start(53, "*", WiFi.softAPIP());

    Serial.println("Access point started");
    Serial.print("SSID: ");
    Serial.println(HOSTNAME + randomStr);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP().toString());
}



void AutomathausESPWifiNetworking::housekeeping(){
    unsigned long currentMillis = millis();
    if(_connectionStatus == NET_SETUP){
        _dnsServer.processNextRequest();

        // if (currentMillis - _previousMillis >= 5000) {
        //     _previousMillis = currentMillis;
        //     connectToNetwork();
        // }
    }
}


bool AutomathausESPWifiNetworking::findServerIPAddress(){
    // Initialize mDNS
    if (!MDNS.begin(HOSTNAME)) {
        Serial.println("Error starting mDNS");
        return false;
    }
    // Search for all services of the specified type
    int n = MDNS.queryService(SERVER_SERVICE_NAME, "tcp");

    // save the first IP address found
    if (n > 0) {
        Serial.printf("Found Automathaus server at %s\n", MDNS.IP(0).toString().c_str());
        strncpy(_serverIPAddress, MDNS.IP(0).toString().c_str(), 16);
        _serverPort = MDNS.port(0);
        _connectedToAutomathausServer = true;
    }else{
        Serial.println("No Automathaus server found");
        _connectedToAutomathausServer = false;
    }

    return _connectedToAutomathausServer;
}

bool AutomathausESPWifiNetworking::isConnectedToAutomathausServer(){
    return _connectedToAutomathausServer;
}

char* AutomathausESPWifiNetworking::getServerIPAddress(){
    return _serverIPAddress;
}

int AutomathausESPWifiNetworking::registerNode(char *idBuffer,const char* nodeName, const char* nodeType){
    HTTPClient http;
    http.begin(_serverIPAddress, _serverPort, "/registerNode");
    http.addHeader("Content-Type", "application/json");

    JsonDocument docRequest;
    docRequest["nodeName"] = nodeName;
    docRequest["ip"] = _IPAddress;
    docRequest["macAddress"] = _MACAddress;
    docRequest["nodeType"] = nodeType;

    std::string jsonString;
    serializeJson(docRequest, jsonString);
    int httpResponseCode = http.POST(jsonString.c_str());
    
    String response;
    if(httpResponseCode == 200){
        response = http.getString();
        JsonDocument docResponse;

        DeserializationError error = deserializeJson(docResponse, response.c_str());
        if (error) {
            Serial.println(error.c_str());
            return -1;
        }

        const char* id = docResponse["id"];
        if (id != NULL) {
            strncpy(idBuffer, id, 15);
        }
    }else{
        Serial.println("Error registering node:");
        Serial.println(httpResponseCode + " - " + response);
        return -1;
    }

    return 0;
}