#include <zephyr/net/coap.h>
#include <zephyr/net/socket.h>
#include <zephyr/logging/log.h>
#include "coap_client.h"

LOG_MODULE_REGISTER(coap_client, LOG_LEVEL_INF);

#define SERVER_PORT 5683
#define MAX_BUF_LEN 128

void send_coap_request(const char *server_ip, const char *resource_path)
{
    int sock;
    struct sockaddr_in6 server_addr;
    uint8_t request_buf[MAX_BUF_LEN];
    uint8_t token[8] = {0x1, 0x2, 0x3, 0x4};
    uint8_t response_buf[MAX_BUF_LEN];
    struct coap_packet request;
    struct coap_packet response;
    int ret;

    sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        LOG_ERR("Failed to create socket");
        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(SERVER_PORT);
    inet_pton(AF_INET6, server_ip, &server_addr.sin6_addr);

    ret = coap_packet_init(&request, request_buf, sizeof(request_buf),
                           1, COAP_TYPE_CON, sizeof(token), &token,
                           COAP_METHOD_GET, coap_next_id());
    if (ret < 0) {
        LOG_ERR("Failed to init CoAP packet");
        close(sock);
        return;
    }

    coap_packet_append_option(&request, COAP_OPTION_URI_PATH, resource_path, strlen(resource_path));

    ret = sendto(sock, request.data, request.max_len, 0,
                 (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        LOG_ERR("Failed to send CoAP request");
        close(sock);
        return;
    }

    LOG_INF("CoAP request sent to [%s]/%s", server_ip, resource_path);

    struct sockaddr_in6 from_addr;
    socklen_t from_len = sizeof(from_addr);
    ret = recvfrom(sock, response_buf, sizeof(response_buf), 0,
                   (struct sockaddr *)&from_addr, &from_len);
    if (ret < 0) {
        LOG_ERR("Failed to receive response");
        close(sock);
        return;
    }

    ret = coap_packet_parse(&response, response_buf, ret, NULL, 0);
    if (ret < 0) {
        LOG_ERR("Failed to parse response");
        close(sock);
        return;
    }

    const uint8_t *payload = coap_packet_get_payload(&response, NULL);
    if (payload) {
        LOG_INF("Received payload: %s", payload);
    } else {
        LOG_WRN("No payload in response");
    }

    close(sock);
}
