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

class Automathaus {
public:
    Automathaus(AutomathausWebServer *webServer);
    ~Automathaus();

    void start();
    AutomathausState getState();

private:
    AutomathausWebServer *webServer;
    AutomathausState state;
};

#endif // AUTOMATHAUS_H