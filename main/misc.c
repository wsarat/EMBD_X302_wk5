#include "misc.h"

#define WHATSAPP_PHONE  "16506096944"
#define WHATSAPP_KEY    "5302599"

temperature_sensor_handle_t temp_sensor = NULL;
static pthread_mutex_t extTempMutex;

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
    snprintf(url, 128, "https://api.callmebot.com/whatsapp.php?phone=%s&text=%s&apikey=%s", WHATSAPP_PHONE, url_encode(text), WHATSAPP_KEY);
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
    //gpio_set_level(LED_PIN, on);
    //return gpio_get_level(LED_PIN);

    if (on) {
        printf("Turn LED On\n");
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY_100));
    } else {
        printf("Turn LED Off\n");
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0));
    }
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));

    return 0;
    
}

int misc_led_level(int pct) {
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, pct*LEDC_DUTY_100/100 ));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));

    return 0;
    
}

float misc_temp_read() {
    float tempC;

    ESP_ERROR_CHECK(temperature_sensor_enable(temp_sensor));
    ESP_ERROR_CHECK(temperature_sensor_get_celsius(temp_sensor, &tempC));
    //printf("Temperature is %.02f °C\n", tempC);
    ESP_ERROR_CHECK(temperature_sensor_disable(temp_sensor));   

    return tempC;
}

void misc_ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LED_PIN,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void misc_init() {
    // led pin init
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // internal temp sensors
    temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 50);
    temperature_sensor_install(&temp_sensor_config, &temp_sensor);

    misc_ledc_init();
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0));

    if(pthread_mutex_init (&extTempMutex, NULL) != 0){
        printf("Failed to initialize the sliderMutex mutex");
    }
}

void misc_whatsapp_temp() {
    float temp = misc_temp_read();
    char text[64];

    snprintf(text,64,"ESP32 internet temp = %.02f C", temp);
    printf("text");
    
    //misc_whatsapp(text);
}

void misc_read_extTemp() {
    float extTempC = ds18b20_cmd_read_temp();
    printf("extTemp: %.02f\n", extTempC);
    
    if (extTempC < -126.0 || extTempC > 127.0)
        return;
    
    if (pthread_mutex_trylock(&extTempMutex) == 0){
        _extTempC = extTempC;
        pthread_mutex_unlock(&extTempMutex);
    }
}

float misc_get_extTemp() {
    float extTempC = -127.0;
    if (pthread_mutex_lock(&extTempMutex) == 0){
        extTempC = _extTempC;
        pthread_mutex_unlock(&extTempMutex);
    }

    return extTempC;
}
