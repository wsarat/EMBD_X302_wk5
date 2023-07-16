#include "misc.h"

int misc_led(int on) {
    gpio_set_level(LED_PIN, on);

    return gpio_get_level(LED_PIN);
}

void misc_init() {
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, 1);
}