#include <zephyr/kernel.h>
#include <zephyr/net/openthread.h>
#include <openthread/thread.h>
#include <openthread/coap.h>

#include "network.h"
#include "errors.h"

#define TIMEOUT 1000

int initialize_server() {
    return 0;
}

int initialize_client() {
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