#include <stdio.h>


#include "handler_ll.h"
#include "errors.h"



static handler_node* head;


int handler_add(otCoapResource* requestHandler) {
    if (requestHandler == NULL) {
        return ENULLARG;
    }

    if (head == NULL) {
        return 0;
    }

    return 0;
}