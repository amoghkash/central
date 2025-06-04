#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include <openthread/coap.h>

#define MAX_HANDLER_NAME_SIZE   20

typedef struct handler_node_t handler_node;

struct handler_node_t {
    char name[MAX_HANDLER_NAME_SIZE];   // Name of function
    mesh_handler *cb;                   // Callback function
    handler_node *next;                 // Next node
};


/**
 * Function to add handler to the mesh request network
 */
int handler_add(char* name, mesh_handler *callback);

/**
 * @brief Handles a mesh message with all registered handlers.
 * 
 * This function processes the given mesh message.
 * 
 * @param messageToHandle Pointer to the mesh message to be handled.
 * @return An integer indicating the result of the message handling.
 *         0 indicates success, while non-zero values indicate
 */
int ot_message_handle(meshMessage *messageToHandle);

#ifdef __cplusplus
}
#endif


