#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/net/openthread.h>
#include <openthread/thread.h>
#include <openthread/coap.h>

#include "network.h"
#include "errors.h"

#define TIMEOUT 1000


int initialize_coap() {
    otError error;
    otInstance *t_instance = openthread_get_default_instance();

    error = otCoapStart(t_instance, OT_DEFAULT_COAP_PORT);
    if (error != OT_ERROR_NONE) {
        printk("CoAP Initialization Fail: %d\n", error);
        return EOT_FAIL;
    }

    printk("CoAP Initialized Successfully\n");

    return 0;   
}

int deinitialize_coap() {
    otError error;
    otInstance *t_instance = openthread_get_default_instance();

    error = otCoapStop(t_instance);
    if (error != OT_ERROR_NONE) {
        printk("CoAP Initialization Fail: %d\n", error);
        return EOT_FAIL;
    }

    printk("CoAP Initialized Successfully\n");

    return 0;   
}

int addResourceHandler(otCoapResource *resource) {
    if (resource == NULL) {
        return ENULLARG;
    }

    otInstance *t_instance = openthread_get_default_instance();
    if (t_instance == NULL) {       // If instance isn't initalized, fail
        return EOT_NOINIT;
    }
    
    resource->mContext = t_instance;
    otCoapAddResource(t_instance, resource);

    return 0;
}
