#pragma once
#ifndef AUTOMATHAUS_H
#define AUTOMATHAUS_H

#include <Arduino.h>
#include <DNSServer.h>

#include "AutomathausESPWifiNetworking.h"
#include "AutomathausWebServer.h"
#include "AutomathausAsyncWebServer.h"
#include "AutomathausState.h"
#include "AutomathausNetworking.h"
#include "AutomathausKVSEspPreferences.h"
#include "./generated/webgui.h"


class Automathaus {
private:
    AutomathausWebServer &_webServer;
    AutomathausNetworking &_networking;
    AutomathausKeyValueStore &_kvStore;
    AutomathausState _state;

public:
    Automathaus(AutomathausNetworking &networking, AutomathausWebServer &webServer, AutomathausKeyValueStore &kvStore);
    ~Automathaus();

    void start(const char* nodeType, int serialBaudrate = 115200);
    void housekeeping();
    AutomathausState getState();
};

#endif // AUTOMATHAUS_H