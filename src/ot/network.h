#pragma once

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Initialize necessary CoAP resources.
 */
int initialize_coap();

/**
 * Deinitialize CoAP resources.
 */
int deitialize_coap();

/**
 * Add a resource handler to the CoAP server.
 * 
 * @param resource Pointer to the resource to be added.
 * @return An integer indicating the result of the resource addition.
 *         0 indicates success, while non-zero values indicate failure
 */
int addResourceHandler(otCoapResource *resource);



#ifdef __cplusplus
}
#endif

