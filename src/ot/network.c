#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/net/openthread.h>
#include <openthread/thread.h>
#include <openthread/coap.h>

#include "network.h"
#include "errors.h"

#define TIMEOUT 1000

int initialize_server() {
    otError error;
    otInstance *t_instance = openthread_get_default_instance();

    error = otCoapStart(t_instance, OT_DEFAULT_COAP_PORT);
    if (error != OT_ERROR_NONE) {
        goto fail;
    }
    otCoapAddResource(t_instance, NULL);
    return 0;

fail:
    return EOT_FAIL;
}

int initialize_client() {
    printk("Client initialization\n");
    return 0;
}

int initialize_mesh() {
    #ifdef CONFIG_COAP_SERVER_ROLE
        return initialize_server();
    #elif CONFIG_COAP_SERVER_ROLE
        return initialize_client();
    #else
        return EOT_FAIL;
    #endif
}