#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <zephyr/kernel.h>
#include <zephyr/net/openthread.h>
#include <openthread/thread.h>
#include <openthread/coap.h>

typedef struct meshMessage {
    char* message;
    int size;
} meshMessage_t;

typedef void (*cb_mesh_request)(void *aContext, otMessage *aMessage, const otMessageInfo *aMessageInfo);


typedef enum messageType {
    CONFIRMABLE     = 0, ///< Confirmable           - Requires an Acknowledgeable
    NON_CONFIRMABLE = 1, ///< Non-confirmable       - Doesn't require an acknowledge
    ACKNOWLEDGMENT  = 2, ///< Acknowledgment        - Message is an Acknowledgement
    RESET           = 3, ///< Reset                 - Not sure what this is
} messageType;


int mesh_initialize();

// int mesh_connect();
// int mesh_send();
// int getMessages();
// int mesh_disconnect();


#ifdef __cplusplus
}
#endif

