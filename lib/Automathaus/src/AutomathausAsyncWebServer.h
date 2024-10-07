#ifndef AUTOMATHAUSASYNCWEBSERVER_H
#define AUTOMATHAUSASYNCWEBSERVER_H

#include "Automathaus.h"
#include "AutomathausWebServer.h"

// Implementazione dell'interfaccia AutomathausWebServer
class AutomathausAsyncWebServer : public AutomathausWebServer {
   private:
    AsyncWebServer *server;

   public:
    AutomathausAsyncWebServer(AsyncWebServer *server) : server(server) {};
    ~AutomathausAsyncWebServer();

    void setWebInterface(AutomathausState) override;
    void onNotFound() override;
    void begin() override;
};

#endif  // AUTOMATHAUSASYNCWEBSERVER_H