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
#include "AutomathausCryptoRSAMbed.h"

class AutomathausESPWifiNetworking : public AutomathausNetworking {
    private:
        DNSServer _dnsServer;
        unsigned long _previousMillis = 0;
        
        char _ssid[33];
        char _password[65];

    public:
        AutomathausESPWifiNetworking(const char* ssid, const char* password);
        ~AutomathausESPWifiNetworking();
        
        void setCredentials(const char* ssid, const char* password);
        char* getIPAddress() override;
        char* getMACAddress() override;
        ConnectionStatus connectToNetwork() override;
        void disconnectFromNetwork() override;
        ConnectionStatus getConnectionStatus() override;
        
        static std::string scanWifiNetworks();

        void startSetupMode() override;
        void housekeeping() override;
};

#endif  // AUTOMATHAUSESPWIFINETWORKING_H