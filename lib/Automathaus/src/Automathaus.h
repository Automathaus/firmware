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
#include "webgui.h"


class Automathaus {
private:
    AutomathausWebServer *webServer;
    AutomathausNetworking *networking;
    AutomathausState state;

public:
    Automathaus(AutomathausNetworking *networking, AutomathausWebServer *webServer);
    ~Automathaus();

    void start(int serialBaudrate = 115200);
    AutomathausState getState();
};

#endif // AUTOMATHAUS_H