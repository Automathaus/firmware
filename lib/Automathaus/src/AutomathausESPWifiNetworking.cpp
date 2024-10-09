#include "AutomathausESPWifiNetworking.h"


AutomathausESPWifiNetworking::AutomathausESPWifiNetworking(const char* ssid, const char* password) {
    setCredentials(ssid, password);
}

AutomathausESPWifiNetworking::~AutomathausESPWifiNetworking() {
    // Destructor
}


void AutomathausESPWifiNetworking::setCredentials(const char* ssid, const char* password) {
    // Set the credentials for the WiFi network
    if (ssid == NULL || password == NULL) {
        _connectionStatus = NET_FAILED;
        return;
    }

    strncpy(_ssid, ssid, 32);
    strncpy(_password, password, 64);
}

void AutomathausESPWifiNetworking::connectToNetwork() {
    // Connect to the WiFi network
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
}

char* AutomathausESPWifiNetworking::getIPAddress() {
    // Get the IP address of the device
    strncpy(_IPAddress, WiFi.localIP().toString().c_str(), 16);
    return _IPAddress;
}

char* AutomathausESPWifiNetworking::getMACAddress() {
    // Get the MAC address of the device
    strncpy(_MACAddress, WiFi.macAddress().c_str(), 18);
    return _MACAddress;
}

ConnectionStatus AutomathausESPWifiNetworking::getConnectionStatus() {
    return _connectionStatus;
}