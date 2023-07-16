#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "wifi.h"

void nvs_init() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);    
}

void app_main(void)
{
    nvs_init();
    wifi_init();
    wifi_connect("CefiroIOT", "CefiroA32");

    uint16_t ap_count = 16; //will ne changed after wifi_scan called
    struct ap_info_t ap_list[ap_count];

    while (true) {
        wifi_scan(&ap_list, &ap_count);

        for (int i=0; i<ap_count; i++) {
            printf("%02X:%02X:%02X:%02X:%02X:%02X : ftm %lX, %lX : %s\n",
                ap_list[i].mac[0], ap_list[i].mac[1], ap_list[i].mac[2], ap_list[i].mac[3], ap_list[i].mac[4], ap_list[i].mac[5],
                ap_list[i].ftm_initiator, ap_list[i].ftm_responder, 
                ap_list[i].ssid
            );
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
