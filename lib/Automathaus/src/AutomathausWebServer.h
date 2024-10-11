#ifndef AUTOMATHAUSWEBSERVER_H
#define AUTOMATHAUSWEBSERVER_H

#include "AutomathausState.h"
class AutomathausWebServer {
   protected:
    AutomathausWebServerMode _mode;

   public:
    AutomathausWebServer(){};
    virtual ~AutomathausWebServer(){};

    /**
     * @brief Set the web interface, this function is used to set the base page that will be shown to the user,
     * it has to implement the root route handling and the "/getRoute" route that will be used to get the current route
     * for the client side router. Why not use the router directly? To save space reusing components in a sigle SPA
     * instead of having multiple pages.
     *
     * @param webPage The html code for the web app
     */
    virtual void setWebInterface(const char *webPage) = 0;

    /**
     * @brief Set the wifi scanner route (/wifiScan), return a json with the name of the ssids and the strength of the signals
     */
    virtual void setWifiScannerRoute() = 0; // -> has to move into a child class that sets the interface for WifiNetworking

    virtual void setMode(AutomathausWebServerMode mode) {
        _mode = mode;
    };

    virtual AutomathausWebServerMode getMode() {
        return _mode;
    };

    virtual void onNotFound() = 0;
    virtual void begin() = 0;
};

#endif  // AUTOMATHAUSWEBSERVER_H