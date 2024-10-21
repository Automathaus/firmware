#ifndef AUTOMATHAUSEKEYVALUESTORE_H
#define AUTOMATHAUSEKEYVALUESTORE_H

class AutomathausKeyValueStore {
    public:
        virtual ~AutomathausKeyValueStore() = default;

        virtual void clearAll();

        virtual void setNodeName(const char* nodeName);
        virtual void setNodeID(const char* nodeID);
        virtual void setWifiCredentials(const char* ssid, const char* password);
        virtual void setOperationalMode(const char* operationalMode);
        virtual void setNodeType(const char* nodeType);

        virtual String getNodeName();
        virtual String getNodeID();
        virtual String getNodeType();
        virtual String getOperationalMode();
};

#endif  // AUTOMATHAUSEKEYVALUESTORE_H