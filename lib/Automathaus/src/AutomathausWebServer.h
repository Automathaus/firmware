#ifndef AUTOMATHAUSWEBSERVER_H
#define AUTOMATHAUSWEBSERVER_H

#include "AutomathausState.h" // Includi AutomathausState

class AutomathausWebServer {
   public:
    AutomathausWebServer(){};
    virtual ~AutomathausWebServer(){};

    virtual void setWebInterface(AutomathausState state) = 0;
    virtual void onNotFound() = 0;
    virtual void begin() = 0;
};

#endif  // AUTOMATHAUSWEBSERVER_H