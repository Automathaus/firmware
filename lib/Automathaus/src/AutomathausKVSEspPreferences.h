#ifndef AUTOMATHAUSEKVSESPPREFERENCES_H
#define AUTOMATHAUSEKVSESPPREFERENCES_H

#include <Preferences.h>
#include "AutomathausKeyValueStore.h"

class AutomathausKVSEspPreferences : public AutomathausKeyValueStore {
    private:

    public:
        Preferences _preferences;
        AutomathausKVSEspPreferences();
        virtual ~AutomathausKVSEspPreferences();

        bool begin() override;
        bool clearAll() override;

        void setNodeName(const char* nodeName) override;
        void setNodeID(const char* nodeID) override;
        void setWifiCredentials(const char* ssid, const char* password) override;
        void setOperationalMode(const char* operationalMode) override;
        void setNodeType(const char* nodeType) override;

        String getNodeName() override;
        String getNodeID() override;
        String getNodeType() override;
        String getWifiSSID();
        String getWifiPassword();
        String getOperationalMode() override;
};

#endif  // AUTOMATHAUSEKVSESPPREFERENCES_H