#ifndef HEADER_MISC_H
#define HEADER_MISC_H

#include "driver/gpio.h"
#include "driver/temperature_sensor.h"

#include "wifi.h"
#include "httpClient.h"

#define LED_PIN GPIO_NUM_2

void misc_http_get(const char* url);
void misc_wifi_scan();
int misc_led(int on);
float misc_temp_read();
void misc_init();

#endif