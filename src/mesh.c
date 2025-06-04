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

static void coap_response_handler(void *t_context, otMessage *t_message, const otMessageInfo *t_message_info)
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
    message.token = *otCoapMessageGetToken(t_message);


    ot_message_handle(&message);



    if (messageType == CONFIRMABLE) {
        //response goes here
        return;
    }
}

static otCoapResource main_handler = {
    .mUriPath = "mainhandler",
    .mHandler = coap_response_handler,
    .mContext = NULL,
    .mNext = NULL
};

int mesh_initialize() {
    int ret = initialize_coap();
    if (ret != 0) {
        return ret;
    }

    ret = configureIP();
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

int configureIP() {
    otInstance *t_instance = openthread_get_default_instance();
    otNetifAddress address;
    const otMeshLocalPrefix *mlp = otThreadGetMeshLocalPrefix(t_instance);
    uint8_t ip[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
    memcpy(&address.mAddress.mFields.m8[0], mlp, 8);
    memcpy(&address.mAddress.mFields.m8[8], ip, 8);

    otError error = otIp6AddUnicastAddress(t_instance, &address);

    if (error != OT_ERROR_NONE) {
        printk("Error configuring IPv6 Address: %d\n", error);
        return EOT_FAIL;
    }
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

int mesh_send(meshPacket *packet) {
    if (packet == NULL) {
        return ENULLARG;
    }
    otError error = OT_ERROR_NONE;
    otMessage *message;
    otMessageInfo messageInfo;
    otInstance *t_instance = openthread_get_default_instance();

    if (t_instance == NULL) {
        printk("Error with ot instance\n");
        return EOT_FAIL;
    }

    const otMeshLocalPrefix *mlp = otThreadGetMeshLocalPrefix(t_instance);
    
    message = otCoapNewMessage(t_instance, NULL);
    if (message == NULL) {
        printk("Failed Message Allocation");
        return EOT_FAIL;
    }

    otCoapMessageInit(message, packet->type, OT_COAP_CODE_PUT);

    error = otCoapMessageAppendUriPathOptions(message, "comms");
    if (error != OT_ERROR_NONE) {goto exit;}

    error = otCoapMessageAppendContentFormatOption(message, OT_COAP_OPTION_CONTENT_FORMAT_JSON);
    if (error != OT_ERROR_NONE) {goto exit;}

    error = otCoapMessageSetPayloadMarker(message);
    if (error != OT_ERROR_NONE) {goto exit;}

    error = otMessageAppend(message, packet->message, packet->message_size);
    if (error != OT_ERROR_NONE) {goto exit;}

    memset(&messageInfo, 0, sizeof(messageInfo));
    memcpy(&messageInfo.mPeerAddr.mFields.m8[0], mlp, 8);
    memcpy(&messageInfo.mPeerAddr.mFields.m8[8], packet->device_id, 8);
    messageInfo.mPeerPort = OT_DEFAULT_COAP_PORT;

    error = otCoapSendRequest(t_instance, message, &messageInfo, NULL, NULL);
    printk("CoAP Data Sent.\n");
exit:
    if (error != OT_ERROR_NONE) {
        printk("Failed to send CoAP Request: %d\n", error);
        otMessageFree(message);
        return EOT_FAIL;
    }
    
    return 0;
}

 