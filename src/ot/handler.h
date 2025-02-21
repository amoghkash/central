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
    handler_node* next;                 // Next node
};


/**
 * Function to add handler to the mesh request network
 */
int handler_add(char* name, mesh_handler *callback);

/**
 * @brief Handles a mesh message.
 *
 * This function processes the given mesh message and performs the necessary
 * actions based on the message content.
 *
 * @param messageToHandle Pointer to the mesh message to be handled.
 * @return An integer indicating the result of the message handling.
 *         Typically, 0 indicates success, while non-zero values indicate
 *         an error or specific handling result.
 */
int ot_message_handle(meshMessage *messageToHandle);

#ifdef __cplusplus
}
#endif


