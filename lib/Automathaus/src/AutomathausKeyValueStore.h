#ifndef AUTOMATHAUSEKEYVALUESTORE_H
#define AUTOMATHAUSEKEYVALUESTORE_H

class AutomathausKeyValueStore {
    public:
        virtual ~AutomathausKeyValueStore() = default;

        virtual bool begin() = 0;
        virtual bool clearAll() = 0;

        virtual void setNodeName(const char* nodeName) = 0;
        virtual void setNodeID(const char* nodeID) = 0;
        virtual void setWifiCredentials(const char* ssid, const char* password) = 0;
        virtual void setOperationalMode(const char* operationalMode) = 0;
        virtual void setNodeType(const char* nodeType) = 0;

        virtual String getNodeName() = 0;
        virtual String getNodeID() = 0;
        virtual String getNodeType() = 0;
        virtual String getWifiSSID() = 0;
        virtual String getWifiPassword() = 0;
        virtual String getOperationalMode() = 0;
};

#endif  // AUTOMATHAUSEKEYVALUESTORE_H