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
#include "AutomathausCrypto.h"


// Implementazione dell'interfaccia AutomathausWebServer
class AutomathausAsyncWebServer : public AutomathausWebServer {
   private:
    constexpr static const size_t _maxContentLength = 16384;
    AsyncWebServer &_server;
    AutomathausCrypto &_crypto;

   public:
    AutomathausAsyncWebServer(AsyncWebServer &server, AutomathausCrypto &crypto) : _server(server), _crypto(crypto) {};
    ~AutomathausAsyncWebServer();

    void setResetMode() {
        _mode = WEB_SERVER_RESET_MODE;
    };

    void setWebInterface(const char *webPage) override;
    void setGeneratedBindings() override;

    static void handleBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
    size_t decryptEncryptedBody(AsyncWebServerRequest *request);
    void begin() override;
};

#endif  // AUTOMATHAUSASYNCWEBSERVER_H