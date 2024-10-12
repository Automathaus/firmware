#ifndef AUTOMATHAUSWEBSERVER_H
#define AUTOMATHAUSWEBSERVER_H

#include "AutomathausState.h"

namespace Routes {
    constexpr char ROOT[] = "/";
    constexpr char RESET[] = "/reset";
}

class AutomathausWebServer {
   protected:
    AutomathausWebServerMode _mode;
    constexpr static const char *JSON_TEMPLATE = "{\"route\":\"%s\"}";

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
    virtual void onNotFound() = 0;
    virtual void begin() = 0;

    virtual void setResetMode() {
        _mode = WEB_SERVER_RESET_MODE;
    };

    virtual void setNormalMode() {
        _mode = WEB_SERVER_NORMAL_MODE;
    };

    virtual AutomathausWebServerMode getMode() {
        return _mode;
    };
};

#endif  // AUTOMATHAUSWEBSERVER_H