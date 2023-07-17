#include "misc.h"

#define WHATSAPP_PHONE  "16506096944"
#define WHATSAPP_KEY    "5302599"

temperature_sensor_handle_t temp_sensor = NULL;

char *url_encode(const unsigned char *str)
{
    static const char *hex = "0123456789abcdef";
    static char encoded[1024];
    char *p = encoded;
    while (*str)
    {
        if (isalnum(*str) || *str == '-' || *str == '_' || *str == '.' || *str == '~')
        {
            *p++ = *str;
        }
        else
        {
            *p++ = '%';
            *p++ = hex[*str >> 4];
            *p++ = hex[*str & 15];
        }
        str++;
    }
    *p = '\0';
    return encoded;
}

void misc_whatsapp(const unsigned * text) {
    char url[128];
    sprintf(url, "https://api.callmebot.com/whatsapp.php?phone=%s&text=%s&apikey=%s", WHATSAPP_PHONE, url_encode(text), WHATSAPP_KEY);
    misc_http_get(url);
}

void misc_wifi_scan() {
    uint16_t ap_count = 8; //will ne changed after wifi_scan called
    struct ap_info_t ap_list[ap_count];
    wifi_scan(&ap_list, &ap_count);

    for (int i=0; i<ap_count; i++) {
        printf("%02X:%02X:%02X:%02X:%02X:%02X : ftm %lX, %lX : %s\n",
            ap_list[i].mac[0], ap_list[i].mac[1], ap_list[i].mac[2], ap_list[i].mac[3], ap_list[i].mac[4], ap_list[i].mac[5],
            ap_list[i].ftm_initiator, ap_list[i].ftm_responder, 
            ap_list[i].ssid
        );
    }
}

void misc_http_get(const char* url) {
    char response_buffer[MAX_HTTP_OUTPUT_BUFFER] = {0};
    int ret;
    
    ret = httpClient_get(url, response_buffer);
    printf("%s\n", response_buffer);   
}

int misc_led(int on) {
    gpio_set_level(LED_PIN, on);

    return gpio_get_level(LED_PIN);
}

float misc_temp_read() {
    float tsens_value;
    temperature_sensor_get_celsius(temp_sensor, &tsens_value);

    return tsens_value;
}

void misc_init() {
    // led pin init
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // internal temp sensors
    temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 50);
    temperature_sensor_install(&temp_sensor_config, &temp_sensor);
    temperature_sensor_enable(temp_sensor);

}