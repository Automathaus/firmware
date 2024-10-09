#ifndef AUTOMATHAUSNETWORKING_H
#define AUTOMATHAUSNETWORKING_H

typedef enum {
    WiFi_DISCONNECTED,
    WiFi_CONNECTED,
    WiFi_FAILED,
} ConnectionStatus;

class AutomathausNetworking {
    protected:
        ConnectionStatus connectionStatus = WiFi_DISCONNECTED;
        char IPAddress[16];
        char MACAddress[18];
        
    public:
        AutomathausNetworking() {};
        virtual ~AutomathausNetworking() {};

        virtual void setCredentials(const char* ssid, const char* password) = 0;
        virtual void connectToNetwork() = 0;
        virtual char* getIPAddress() = 0;
        virtual char* getMACAddress() = 0;
        virtual ConnectionStatus getConnectionStatus() = 0;
};


#endif  // AUTOMATHAUSNETWORKING_H