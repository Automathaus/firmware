#ifndef AUTOMATHAUSWEBSERVER_H
#define AUTOMATHAUSWEBSERVER_H

class AutomathausWebServer {
   public:
    AutomathausWebServer(){};
    virtual ~AutomathausWebServer(){};

    virtual void setWebInterface(const char *webPage) = 0;
    virtual void onNotFound() = 0;
    virtual void begin() = 0;
};

#endif  // AUTOMATHAUSWEBSERVER_H