#ifndef AUTOMATHAUSEKVSESPPREFERENCES_H
#define AUTOMATHAUSEKVSESPPREFERENCES_H

#include <Preferences.h>
#include "AutomathausKeyValueStore.h"

class AutomathausKVSEspPreferences : public AutomathausKeyValueStore {
    private:
        Preferences _preferences;

    public:
        AutomathausKVSEspPreferences();
        virtual ~AutomathausKVSEspPreferences();

        void setNodeName(const char* nodeName) override;
        void setNodeID(const char* nodeID) override;
        void setWifiCredentials(const char* ssid, const char* password) override;
        void setOperationalMode(const char* operationalMode) override;
        void setNodeType(const char* nodeType) override;

        const char* getNodeName() override;
        const char* getNodeID() override;
        const char* getNodeType() override;
        const char* getWifiSSID();
        const char* getWifiPassword();
        const char* getOperationalMode() override;
};

#endif  // AUTOMATHAUSEKVSESPPREFERENCES_H