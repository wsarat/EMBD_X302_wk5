#ifndef HEADER_WIFI_H
#define HEADER_WIFI_H

#include "esp_log.h"

#include "esp_wifi.h"
#include "esp_event.h"  //esp_event_loop_create_default
#include "freertos/event_groups.h"  //xEventGroupSetBits

#include "lwip/err.h"   // netif
#include "lwip/sys.h"

void wifi_init();

#endif