#ifndef HEADER_MISC_H
#define HEADER_MISC_H

#include "driver/gpio.h"
#include "driver/temperature_sensor.h"
#include "driver/ledc.h"

#include "wifi.h"
#include "httpClient.h"

#define LED_PIN GPIO_NUM_2

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY_50            (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_DUTY_20            (1638) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_DUTY_100           (8191) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz

void misc_http_get(const char* url);
void misc_wifi_scan();
int misc_led(int on);
float misc_temp_read();
void misc_init();
void misc_whatsapp(const unsigned * text);
void misc_whatsapp_temp();

#endif