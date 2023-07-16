#ifndef HEADER_WIFI_H
#define HEADER_WIFI_H

#include "esp_log.h"

#include "esp_wifi.h"
#include "esp_event.h"  //esp_event_loop_create_default
#include "freertos/event_groups.h"  //xEventGroupSetBits

#include "lwip/err.h"   // netif
#include "lwip/sys.h"

struct ap_info_t {
    uint8_t mac[6];
    uint8_t ssid[33];
    uint8_t channel;
    uint32_t ftm_responder;
    uint32_t ftm_initiator;
}; 

void wifi_init();
void wifi_scan(struct ap_info_t *ap_list, uint16_t *max);
void wifi_connect(const char* ssid, const char* password);

#endif