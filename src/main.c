#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "coap_server.h"
#include "coap_client.h"

int server = 0;

int main(void)
{
    if (server) {
        printk("Starting CoAP Server\n");
        start_coap_server();
    } else {
        printk("Starting CoAP Client\n");
        send_coap_request("2001:db8::1", "hello");
    }
    return 0;
}
