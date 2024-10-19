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

        constexpr static const char* HOSTNAME = "AutomathausNode";
        constexpr static const char* AP_PASSWORD = "0123456789";

        char _IPAddress[16] = {0};
        char _MACAddress[18] = {0};
        
    public:
        AutomathausNetworking() {};
        virtual ~AutomathausNetworking() {};

        virtual char* getIPAddress() = 0;
        virtual char* getMACAddress() = 0;
        
        virtual ConnectionStatus connectToNetwork() = 0;
        virtual void disconnectFromNetwork() = 0;

        virtual ConnectionStatus getConnectionStatus() = 0;

        virtual void startSetupMode() = 0;
        virtual void housekeeping() = 0;
};


#endif  // AUTOMATHAUSNETWORKING_H