#ifndef AUTOMATHAUSNETWORKING_H
#define AUTOMATHAUSNETWORKING_H

typedef enum {
    NET_SETUP,
    NET_DISCONNECTED,
    NET_CONNECTED,
    NET_FAILED,
} ConnectionStatus;

class AutomathausNetworking {
    protected:
        ConnectionStatus _connectionStatus = NET_DISCONNECTED;

        constexpr static const char* SERVER_SERVICE_NAME = "automathaus";

        bool _connectedToAutomathausServer = false;
        char _serverIPAddress[16] = {0};

        char _IPAddress[16] = {0};
        char _MACAddress[18] = {0};
        
    public:
        constexpr static const char* HOSTNAME = "AutomathausNode";
        
        AutomathausNetworking() {};
        virtual ~AutomathausNetworking() {};

        virtual char* getIPAddress() = 0;
        virtual char* getMACAddress() = 0;
        
        virtual ConnectionStatus connectToNetwork() = 0;
        virtual ConnectionStatus getConnectionStatus() = 0;
        virtual void disconnectFromNetwork() = 0;

        virtual void startSetupMode() = 0;
        virtual void setCredentials(const char* ssid, const char* password) = 0;

        virtual void findServerIPAddress() = 0;
        virtual char* getServerIPAddress() = 0;
        virtual bool isConnectedToAutomathausServer() = 0;
        
        virtual void housekeeping() = 0;
};




#endif  // AUTOMATHAUSNETWORKING_H

#ifndef AUTOMATHAUSWIFI_H
#define AUTOMATHAUSWIFI_H

class AutomathausWifiNetworking : public AutomathausNetworking {
    protected:
        char _ssid[33] = {0};
        char _password[65] = {0};

        constexpr static const char* AP_PASSWORD = "0123456789";

    public:
        AutomathausWifiNetworking() {};
        virtual ~AutomathausWifiNetworking() {};

        virtual std::string scanWifiNetworks() = 0;
};

#endif  // AUTOMATHAUSWIFI_H