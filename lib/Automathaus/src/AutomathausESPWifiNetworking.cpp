#include "AutomathausESPWifiNetworking.h"

std::string AutomathausESPWifiNetworking::_wifiNetworksJson;

AutomathausESPWifiNetworking::AutomathausESPWifiNetworking(const char* ssid, const char* password) {
    setCredentials(ssid, password);
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
    WiFi.disconnect();    // Disconnect from any network
    scanWifiNetworks();
    delay(100); 

    if (_ssid == NULL || _password == NULL) {
        _connectionStatus = NET_FAILED;
        return _connectionStatus;
    }

    WiFi.mode(WIFI_AP_STA);
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


void AutomathausESPWifiNetworking::scanWifiNetworks(){
    _wifiNetworksJson = "[";
    WiFi.mode(WIFI_STA);
    delay(100);

    int n = WiFi.scanNetworks();
    Serial.print("Scanning for WiFi networks...");
    Serial.print("Found ");
    Serial.print(n);
    Serial.println(" networks");

    if (n == 0) {
        Serial.println("No networks found");
    } else {
        for (int i = 0; i < n; ++i) {
            if (i) _wifiNetworksJson += ",";
            _wifiNetworksJson += "{";
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

            _wifiNetworksJson += "\"signalStrength\":" + std::to_string(signal_strength);
            _wifiNetworksJson += ",\"ssid\":\"" + std::string(WiFi.SSID(i).c_str()) + "\"";
            _wifiNetworksJson += ",\"bssid\":\"" + std::string(WiFi.BSSIDstr(i).c_str()) + "\"";
            _wifiNetworksJson += ",\"channel\":" + std::to_string(WiFi.channel(i));
            _wifiNetworksJson += ",\"secure\":\"";

            switch (WiFi.encryptionType(i)) {
                case WIFI_AUTH_OPEN:
                    _wifiNetworksJson += "Open";
                    break;
                case WIFI_AUTH_WEP:
                    _wifiNetworksJson += "WEP";
                    break;
                case WIFI_AUTH_WPA_PSK:
                    _wifiNetworksJson += "WPA-PSK";
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    _wifiNetworksJson += "WPA2-PSK";
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    _wifiNetworksJson += "WPA/WPA2-PSK";
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    _wifiNetworksJson += "WPA2-Enterprise";
                    break;
                default:
                    _wifiNetworksJson += "Sconosciuto";
                    break;
            }
            
            _wifiNetworksJson += "\"";
            _wifiNetworksJson += "}";
        }
        WiFi.scanDelete();
    }
    _wifiNetworksJson += "]";
    Serial.println(_wifiNetworksJson.c_str());
}

std::string AutomathausESPWifiNetworking::getWifiNetworksJson(){
    return _wifiNetworksJson;
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
    // scanWifiNetworks();
    randomSeed(millis());
    String randomStr = "";
    // for (int i = 0; i < 5; i++) {
    //     int randomNumber = random(0, 10); // Generate a random number between 0 and 9
    //     randomStr += String(randomNumber);
    // }

    Serial.println("Starting configuration Access point");
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(HOSTNAME + randomStr, AP_PASSWORD);
    _dnsServer.start(53, "*", WiFi.softAPIP());

    Serial.println("Access point started");
    Serial.print("SSID: ");
    Serial.println(HOSTNAME + randomStr);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP().toString());
}



void AutomathausESPWifiNetworking::housekeeping(){
    // unsigned long currentMillis = millis();
    if(_connectionStatus == NET_SETUP){
        _dnsServer.processNextRequest();

        // if (currentMillis - _previousMillis >= 10000) {
        //     _previousMillis = currentMillis;
        //     connectToNetwork();
        // }
    }
}