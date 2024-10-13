#include "AutomathausAsyncWebServer.h"
#include "AutomathausWebReset.h"

void AutomathausAsyncWebServer::setBindings() {
    _server.on("/bindings/AutomathausWebReset/testBinding", HTTP_GET, [](AsyncWebServerRequest *request) {
        AutomathausWebReset::testBinding();
        request->send(200, "text/plain", "Test binding executed");
    });
}