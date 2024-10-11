#ifndef AUTOMATHAUSESPWIFINETWORKING_H
#define AUTOMATHAUSESPWIFINETWORKING_H

#include <Arduino.h>
#include <DNSServer.h>
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "AutomathausNetworking.h"

class AutomathausESPWifiNetworking : public AutomathausNetworking {
    private:
        char _ssid[33];
        char _password[65];

    public:
        AutomathausESPWifiNetworking(const char* ssid, const char* password);
        ~AutomathausESPWifiNetworking();
        
        void setCredentials(const char* ssid, const char* password);
        void connectToNetwork() override;
        char* getIPAddress() override;
        char* getMACAddress() override;
        ConnectionStatus getConnectionStatus() override;
        
        static std::string scanWifiNetworks();
};

#endif  // AUTOMATHAUSESPWIFINETWORKING_H