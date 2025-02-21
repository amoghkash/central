#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <zephyr/kernel.h>
#include <zephyr/net/openthread.h>
#include <openthread/thread.h>
#include <openthread/coap.h>

#include "types.h"

int mesh_initialize();

// int mesh_connect();
// int mesh_send();
// int getMessages();
// int mesh_disconnect();


#ifdef __cplusplus
}
#endif

