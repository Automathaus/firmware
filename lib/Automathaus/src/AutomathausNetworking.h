#ifndef AUTOMATHAUSNETWORKING_H
#define AUTOMATHAUSNETWORKING_H

typedef enum {
    NET_DISCONNECTED,
    NET_CONNECTED,
    NET_FAILED,
} ConnectionStatus;

class AutomathausNetworking {
    protected:
        ConnectionStatus connectionStatus = NET_DISCONNECTED;
        char IPAddress[16];
        char MACAddress[18];
        
    public:
        AutomathausNetworking() {};
        virtual ~AutomathausNetworking() {};

        virtual void connectToNetwork() = 0;
        virtual char* getIPAddress() = 0;
        virtual char* getMACAddress() = 0;
        virtual ConnectionStatus getConnectionStatus() = 0;
};


#endif  // AUTOMATHAUSNETWORKING_H