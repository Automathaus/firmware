#include "Automathaus.h"

Automathaus::Automathaus(AutomathausWebServer *webServer) : webServer(webServer) {}

Automathaus::~Automathaus() {}

void Automathaus::start(){
    state = NODE_SETUP;

    webServer->setWebInterface(state);
    webServer->onNotFound();
    webServer->begin();
}

AutomathausState Automathaus::getState(){
    return state;
}