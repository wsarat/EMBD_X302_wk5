#include "httpServer.h"

/* A simple example that demonstrates how to create GET and POST
 * handlers and start an HTTPS server.
*/

static const char *HTTPSERVER_TAG = "httpServer";
static pthread_mutex_t sliderMutex;

/* An HTTP GET handler */
static esp_err_t root_get_handler(httpd_req_t *req)
{
    extern const char page1_html[] asm("_binary_page1_html_start");

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, page1_html, HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

static const httpd_uri_t root = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = root_get_handler
};

static esp_err_t httpd_handler_ledOn(httpd_req_t *req)
{
    int led = misc_led(1);
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, "ok", HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

static const httpd_uri_t httpd_ledOn = {
    .uri       = "/ledOn",
    .method    = HTTP_GET,
    .handler   = httpd_handler_ledOn
};

static esp_err_t httpd_handler_ledOff(httpd_req_t *req)
{
    int led = misc_led(0);
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, "ok", HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

static const httpd_uri_t httpd_ledOff = {
    .uri       = "/ledOff",
    .method    = HTTP_GET,
    .handler   = httpd_handler_ledOff
};

static esp_err_t httpd_handler_led(httpd_req_t *req)
{
    if (pthread_mutex_trylock(&sliderMutex) == 0){
        //Access spiffs and perform operations
        char *buf;
        int buf_len = httpd_req_get_url_query_len(req) + 1;
        if (buf_len > 1) {
            buf = malloc(buf_len);
            if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
            {
                //ESP_LOGI(HTTPSERVER_TAG, "Found URL query => %s", buf);
                char param[32];
                /* Get value of expected key from query string */
                if (httpd_query_key_value(buf, "level", param, sizeof(param)) == ESP_OK)
                {
                    //ESP_LOGI(HTTPSERVER_TAG, "Found URL query parameter => level=%s", param);
                    misc_led_level(atoi(param));
                }
            }
            free(buf);
        }
        //Unlock once operations are done
        pthread_mutex_unlock(&sliderMutex);
    }

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, "ok", HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}    

static const httpd_uri_t httpd_led = {
    .uri       = "/led",
    .method    = HTTP_GET,
    .handler   = httpd_handler_led
};    

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;

    // Start the httpd server
    ESP_LOGI(HTTPSERVER_TAG, "Starting server");

    httpd_ssl_config_t conf = HTTPD_SSL_CONFIG_DEFAULT();

    extern const unsigned char servercert_start[] asm("_binary_servercert_pem_start");
    extern const unsigned char servercert_end[]   asm("_binary_servercert_pem_end");
    conf.servercert = servercert_start;
    conf.servercert_len = servercert_end - servercert_start;

    extern const unsigned char prvtkey_pem_start[] asm("_binary_prvtkey_pem_start");
    extern const unsigned char prvtkey_pem_end[]   asm("_binary_prvtkey_pem_end");
    conf.prvtkey_pem = prvtkey_pem_start;
    conf.prvtkey_len = prvtkey_pem_end - prvtkey_pem_start;

    esp_err_t ret = httpd_ssl_start(&server, &conf);
    if (ESP_OK != ret) {
        ESP_LOGI(HTTPSERVER_TAG, "Error starting server!");
        return NULL;
    }

    // Set URI handlers
    ESP_LOGI(HTTPSERVER_TAG, "Registering URI handlers");
    httpd_register_uri_handler(server, &root);
    httpd_register_uri_handler(server, &httpd_ledOn);
    httpd_register_uri_handler(server, &httpd_ledOff);
    httpd_register_uri_handler(server, &httpd_led);
    return server;
}

static esp_err_t stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    return httpd_ssl_stop(server);
}

static httpd_handle_t server = NULL;

void httpServer_stop() {
    if (stop_webserver(server) == ESP_OK) {
        server = NULL;
        ESP_LOGE(HTTPSERVER_TAG, "https server stoped");
    } else {
        ESP_LOGE(HTTPSERVER_TAG, "Failed to stop https server");
    }
}

void httpServer_start() {
    server = start_webserver();
    ESP_LOGE(HTTPSERVER_TAG, "https server started");
}

void httpServer_init(void)
{
    if(pthread_mutex_init (&sliderMutex, NULL) != 0){
        printf("Failed to initialize the sliderMutex mutex");
    }
}
