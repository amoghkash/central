#include <zephyr/net/coap.h>
#include <zephyr/net/socket.h>
#include <zephyr/net/net_pkt.h>
#include <zephyr/net/net_context.h>
#include <zephyr/logging/log.h>
#include "coap_server.h"


LOG_MODULE_REGISTER(coap_server, LOG_LEVEL_INF);

#define MY_PORT 5683
static int sock;

int coap_handler_request(struct coap_resource *resource,
                        struct coap_packet *request,
                        struct sockaddr *addr,
                        socklen_t addr_len)
{
    struct coap_packet response;
    uint8_t data[128];
    uint8_t token;
    int r;

    LOG_INF("Received CoAP request");

    r = coap_packet_init(&response, data, sizeof(data),
                         1, COAP_TYPE_ACK,
                         coap_header_get_token(request, &token),
                         &token,
                         COAP_RESPONSE_CODE_CONTENT,
                         coap_header_get_id(request));
    if (r < 0) {
        LOG_ERR("Failed to init response packet");
        return r;
    }

    coap_packet_append_payload_marker(&response);
    coap_packet_append_payload(&response, (uint8_t *)"Hello from Zephyr!", 18);

    sendto(sock, response.data, response.offset, 0, addr, addr_len);

    return 0;
}

static struct coap_resource resources[] = {
    { .get = coap_handler_request, .path = "hello", .user_data = NULL },
    { }
};

void start_coap_server(void)
{
    struct sockaddr_in6 addr6;
    int ret;

    sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        LOG_ERR("Failed to create UDP socket");
        return;
    }
    printk("Starting Server\n");
    memset(&addr6, 0, sizeof(addr6));
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(MY_PORT);
    addr6.sin6_addr = in6addr_any;

    ret = bind(sock, (struct sockaddr *)&addr6, sizeof(addr6));
    if (ret < 0) {
        LOG_ERR("Failed to bind socket");
        return;
    }

    LOG_INF("CoAP server listening on port %d", MY_PORT);

    while (1) {
        uint8_t buffer[128];
        struct sockaddr client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int received = recvfrom(sock, buffer, sizeof(buffer), 0, &client_addr, &addr_len);
        if (received < 0) {
            continue;
        }

        struct coap_packet request;
        coap_packet_parse(&request, buffer, received, NULL, 0);

        coap_handler_request(&resources[0], &request, &client_addr, addr_len);
    }
}
