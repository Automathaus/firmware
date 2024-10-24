#ifndef AUTOMATHAUSESPWIFINETWORKING_H
#define AUTOMATHAUSESPWIFINETWORKING_H

#include <Arduino.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "AutomathausNetworking.h"
#include "AutomathausCryptoRSAMbed.h"

class AutomathausESPWifiNetworking : public AutomathausWifiNetworking {
    private:
        DNSServer _dnsServer;
        unsigned long _previousMillis = 0;

    public:
        AutomathausESPWifiNetworking(const char* ssid, const char* password);
        AutomathausESPWifiNetworking();
        ~AutomathausESPWifiNetworking();
        
        void setCredentials(const char* ssid, const char* password) override;
        char* getIPAddress() override;
        char* getMACAddress() override;
        ConnectionStatus connectToNetwork() override;
        void disconnectFromNetwork() override;
        ConnectionStatus getConnectionStatus() override;
        
        std::string scanWifiNetworks() override;
        void findServerIPAddress() override;
        char* getServerIPAddress() override;
        bool isConnectedToAutomathausServer() override;
        
        void startSetupMode() override;
        void housekeeping() override;
};

#endif  // AUTOMATHAUSESPWIFINETWORKING_H