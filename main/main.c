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
}
