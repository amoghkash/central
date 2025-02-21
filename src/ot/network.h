#pragma once

#ifdef __cplusplus
extern "C" {
#endif


int initialize_coap();
// int deitialize_coap();

int addHandler(otCoapResource *resource);



#ifdef __cplusplus
}
#endif

