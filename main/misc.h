#ifndef HEADER_MISC_H
#define HEADER_MISC_H

#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2

int misc_led(int on);
void misc_init();

#endif