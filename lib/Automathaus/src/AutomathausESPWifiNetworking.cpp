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
        connectionStatus = NET_FAILED;
        return;
    }

    strncpy(this->ssid, ssid, 32);
    strncpy(this->password, password, 64);
}

void AutomathausESPWifiNetworking::connectToNetwork() {
    // Connect to the WiFi network
    if (ssid == NULL || password == NULL) {
        connectionStatus = NET_FAILED;
        return;
    }

    WiFi.mode(NET_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        connectionStatus = NET_FAILED;
        return;
    }
    connectionStatus = NET_CONNECTED;
}

char* AutomathausESPWifiNetworking::getIPAddress() {
    // Get the IP address of the device
    strncpy(IPAddress, WiFi.localIP().toString().c_str(), 16);
    return IPAddress;
}

char* AutomathausESPWifiNetworking::getMACAddress() {
    // Get the MAC address of the device
    strncpy(MACAddress, WiFi.macAddress().c_str(), 18);
    return MACAddress;
}

ConnectionStatus AutomathausESPWifiNetworking::getConnectionStatus() {
    return connectionStatus;
}
