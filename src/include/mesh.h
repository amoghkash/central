#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <zephyr/kernel.h>
#include <openthread/thread.h>
#include <openthread/coap.h>

#include "types.h"

//static void coap_response_handler(void *t_context, otMessage *t_message, const otMessageInfo *t_message_info);

/**
 * Initialize the mesh network.
 */
int mesh_initialize();
int configureIP();

// int mesh_connect();
// int mesh_send();
// int getMessages();
// int mesh_disconnect();


#ifdef __cplusplus
}
#endif

