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

#endif  // AUTOMATHAUSSTATE_H