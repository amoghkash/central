#include <string.h>
#include <zephyr/kernel.h>
#include "handler.h"
#include "errors.h"
#include "types.h"



static handler_node* head;

handler_node* create_hnode(char* name, mesh_handler *callback, handler_node* next) {
    if ((name == NULL) | (callback == NULL)) {
        return NULL;
    }

    handler_node *newNode = (handler_node*) malloc(sizeof(handler_node));
    if (newNode == NULL) {
        printk("Failed to malloc handler node.\n");
        return NULL;
    }

    strcpy(newNode->name, name);
    newNode->cb = callback;
    newNode->next = next;
    return newNode;
}

void delete_hnode(handler_node* node) {
    if (node == NULL) {
        return;
    }
    free(node->name);
    free(node);
}

int handler_add(char* name, mesh_handler *callback) {
    if (callback == NULL || name == NULL) {
        return ENULLARG;
    }
    handler_node* newHandler = create_hnode(name, callback, NULL);
    if (newHandler == NULL) {
        return ENOMEM_SYS;
    }

    if (head == NULL) {
        head = newHandler;
    } else {
        handler_node* curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newHandler;
    }

    return 0;
}

int ot_message_handle(meshMessage* messageToHandle) {
    if (messageToHandle == NULL) {
        return ENULLARG;
    }

    if (head == NULL) {
        return 0;
    }

    handler_node* curr = head;

    while (curr) {
        printk("Calling %s\n", curr->name);
        mesh_handler handler = *(curr->cb);
        handler(messageToHandle);
        curr = curr->next;
    }

    return 0;
}