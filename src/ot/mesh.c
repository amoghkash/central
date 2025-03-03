#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/net/openthread.h>
#include <openthread/thread.h>
#include <openthread/coap.h>

#include "mesh.h"
#include "network.h"
#include "errors.h"
#include "types.h"
#include "handler.h"

static otCoapResource main_handler = {
    .mUriPath = "mainhandler",
    .mHandler = coap_response_handler,
    .mContext = NULL,
    .mNext = NULL
};

void coap_response_handler(void *t_context, otMessage *t_message, const otMessageInfo *t_message_info)
{
    otCoapCode messageCode = otCoapMessageGetCode(t_message);
    messageType messageType = otCoapMessageGetType(t_message);


    // Only Accept Data, not acknowledgemnts
    printk("Message Type: %d\n", messageType);
    if (messageType != CONFIRMABLE && messageType != NON_CONFIRMABLE ) {
        return;
    }

    meshMessage message;
    uint16_t text_length = otMessageGetLength(t_message);
    char text[text_length + 2];
    text_length = otMessageRead(t_message, otMessageGetOffset(t_message)+1, text, otMessageGetLength(t_message));
    text[text_length + 1] = '\0';
    printk("Message Content: %s\n", text);
    
    strcpy(message.message, text);
    message.size = (int) text_length;


    ot_message_handle(&message);



    if (messageType == CONFIRMABLE) {
        //response goes here
        return;
    }
}

int mesh_initialize() {
    int ret = initialize_coap();
    if (ret != 0) {
        return ret;
    }

    ret = addResourceHandler(&main_handler);
    if (ret != 0) {
        return ret;
    }
    printk("Main Handler was added successfully\n");
    // Default Function Handlers go here
    return 0;
}

int mesh_register_cb(char* name, mesh_handler *callback) {
    if (callback == NULL || name == NULL) {
        return ENULLARG;
    }

    int ret = handler_add(name, callback);
    if (ret != 0) {
        printk("Failed to init OT Handler: %s\n", name);
        return ret;
    }

    printk("Initialized OT Handler: %s\n", name);

    return 0;
}

