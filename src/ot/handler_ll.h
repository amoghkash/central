#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include <zephyr/kernel.h>
#include <zephyr/net/openthread.h>
#include <openthread/coap.h>


typedef struct handler_node_t handler_node;

struct handler_node_t {
    char* name;
    int size;
    otCoapResource* resource;
    handler_node* next;
};


/**
 * Function to add handler to the mesh request network
 */
int handler_add(otCoapResource *requestHandler);


#ifdef __cplusplus
}
#endif


