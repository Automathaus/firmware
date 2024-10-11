#include "AutomathausESPWifiNetworking.h"


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
}

// Connect to the WiFi network
void AutomathausESPWifiNetworking::connectToNetwork() {
    if (_ssid == NULL || _password == NULL) {
        _connectionStatus = NET_FAILED;
        return;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        _connectionStatus = NET_FAILED;
        return;
    }
    _connectionStatus = NET_CONNECTED;
    strncpy(_IPAddress, WiFi.localIP().toString().c_str(), 16);
    strncpy(_MACAddress, WiFi.macAddress().c_str(), 18);
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

            json += "\"signal_strength\":" + std::to_string(signal_strength);
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

// Get the connection status of the device
ConnectionStatus AutomathausESPWifiNetworking::getConnectionStatus() {
    return _connectionStatus;
}