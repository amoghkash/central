#include <stdio.h>
#include <zephyr/kernel.h>
#include <dk_buttons_and_leds.h>
#include "ot/mesh.h"


int main(void)
{
    mesh_initialize();
}
