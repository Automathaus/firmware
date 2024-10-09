#pragma once
#ifndef AUTOMATHAUS_H
#define AUTOMATHAUS_H

#include <Arduino.h>
#include <DNSServer.h>
#ifdef ESP32
#include <AsyncTCP.h>
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "ESPAsyncWebServer.h"
#include "AutomathausWebServer.h"
#include "AutomathausAsyncWebServer.h"
#include "AutomathausState.h"
#include "AutomathausNetworking.h"
#include "AutomathausESPWifiNetworking.h"


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