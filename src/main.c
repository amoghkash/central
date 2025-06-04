#include <stdio.h>
#include <zephyr/kernel.h>
#include "mesh.h"
#include "peripherals.h"
#include "types.h"

int main(void)
{
    testUTILS();
    mesh_initialize();
    meshPacket mptest;
    mptest.category = BROADCAST;
    mptest.type = NON_CONFIRMABLE;
    mptest.message = "hi";
    mptest.message_size = strlen("hi");
    mesh_send(&mptest); 
}
