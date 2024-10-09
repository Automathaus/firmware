#ifndef AUTOMATHAUSASYNCWEBSERVER_H
#define AUTOMATHAUSASYNCWEBSERVER_H

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#include "AutomathausWebServer.h"

// Implementazione dell'interfaccia AutomathausWebServer
class AutomathausAsyncWebServer : public AutomathausWebServer {
   private:
    AsyncWebServer &_server;

   public:
    AutomathausAsyncWebServer(AsyncWebServer &server) : _server(server) {};
    ~AutomathausAsyncWebServer();

    void setWebInterface(const char *webPage) override;
    void onNotFound() override;
    void begin() override;
};

#endif  // AUTOMATHAUSASYNCWEBSERVER_H