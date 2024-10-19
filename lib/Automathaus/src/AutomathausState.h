#ifndef AUTOMATHAUSSTATE_H
#define AUTOMATHAUSSTATE_H

typedef enum {
    START,
    TRY_CONNECT,
    NODE_SETUP,
    CONNECTED,
    SHARING_CRED,
    RUNNING
} AutomathausState;

typedef enum {
    WEB_SERVER_SETUP_MODE,
    WEB_SERVER_NORMAL_MODE
} AutomathausWebServerMode;

#endif  // AUTOMATHAUSSTATE_H