#ifndef AUTOMATHAUSWEBSERVER_H
#define AUTOMATHAUSWEBSERVER_H

#include "AutomathausState.h"
#include <ESPAsyncWebServer.h>

namespace Routes {
    constexpr char ROOT[] = "/";
    constexpr char RESET[] = "/reset";
    constexpr char NOT_FOUND[] = "/404";
}

class AutomathausWebBindings {
   private:
    constexpr static const size_t _maxContentLength = 16384;

   public:
    virtual ~AutomathausWebBindings() {}
    static void handleBody(AsyncWebServerRequest *request, uint8_t *data,size_t len, size_t index, size_t total) {
        if (total > 0 && request->_tempObject == NULL &&
            total < _maxContentLength) {
            request->_tempObject = malloc(total);
        }
        if (request->_tempObject != NULL) {
            memcpy((uint8_t *)(request->_tempObject) + index, data, len);
        }
    }
};

class AutomathausWebServer {
   protected:
    AutomathausWebServerMode _mode = WEB_SERVER_NORMAL_MODE;
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

    virtual void setGeneratedBindings() = 0;
};

#endif  // AUTOMATHAUSWEBSERVER_H