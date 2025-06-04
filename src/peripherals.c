#include <dk_buttons_and_leds.h>
#include <zephyr/kernel.h>
#include "types.h"
#include "peripherals.h"

static void buttonHandler(uint32_t button_state, uint32_t has_changed) {
    uint32_t buttons = button_state & has_changed;

    if (buttons & DK_BTN1_MSK) {
        // Function for Button 1
        meshPacket packet;
        packet.device_id[0] = 0x01;
        packet.message ="MESSAGE";
        packet.category = BROADCAST;
        packet.type = NON_CONFIRMABLE;
        mesh_send(&packet);
    }

    if (buttons & DK_BTN2_MSK) {
        // Function for Button 2
    }

    if (buttons & DK_BTN3_MSK) {
        // Function for Button 3
    }

    if (buttons & DK_BTN4_MSK) {
        // Function for Button 4
    }
}

void configurebutton() {
    int ret = dk_buttons_init(buttonHandler);
    if (ret) {
        printk("Button Initialization Failed (error: %d)", ret);
    }
}

void configureLED() {
    int ret = dk_leds_init();
    if (ret) {
        printk("LED Initialization Failed (error: %d)", ret);
    }
}

void testUTILS() {
    printk("Testing\n");
}