#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/net/openthread.h>
#include <openthread/thread.h>
#include <openthread/coap.h>

#include "mesh.h"
#include "network.h"
#include "errors.h"

static void coap_response_handler(void *t_context, otMessage *t_message, const otMessageInfo *t_message_info);

static otCoapResource main_handler = {
    .mUriPath = "mainhandler",
    .mHandler = coap_response_handler,
    .mContext = NULL,
    .mNext = NULL
};

void coap_response_handler(void *t_context, otMessage *t_message, const otMessageInfo *t_message_info)
{
    otCoapCode messageCode = otCoapMessageGetCode(t_message);
    messageType messageType = (int) otCoapMessageGetType(t_message);


    // Only Accept Data, not aqknowledgemnts
    printk("Message Type: %d\n", messageType);
    if (messageType != CONFIRMABLE && messageType != NON_CONFIRMABLE ) {
        return;
    }

    uint16_t text_length = otMessageGetLength(t_message);
    char *text[text_length + 2];
    text_length = otMessageRead(t_message, otMessageGetOffset(t_message)+1, text, otMessageGetLength(t_message));
    text[text_length + 1] = '\0';
    printk("Message Content: %s\n", *text);
    
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

    ret = addHandler(&main_handler);
    if (ret != 0) {
        return ret;
    }
    // Default Function Handlers go here
    return 0;
}


