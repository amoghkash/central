#include <dk_buttons_and_leds.h>



static void buttonHandler(uint32_t button_state, uint32_t has_changed) {
    uint32_t buttons = button_state & has_changed;

    if (buttons & DK_BTN1_MSK) {
        // Function for Button 1
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

void configureButtons() {
    int ret = dk_buttons_init(buttonHandler);
    if (ret) {
        LOG_ERR("Button Initialization Failed (error: %d)", ret);
    }
}

void configureLED() {
    int ret = dk_leds_init();
    if (ret) {
        LOG_ERR("LED Initialization Failed (error: %d)", ret);
    }
}