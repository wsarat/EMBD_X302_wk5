#ifndef HEADER_HTTPCLIENT_H
#define HEADER_HTTPCLIENT_H

#include "esp_tls.h"
#include "esp_http_client.h"
#include "wifi.h"

#include <string.h>
#include <sys/param.h> // MIN

#define MAX_HTTP_RECV_BUFFER 512
#define MAX_HTTP_OUTPUT_BUFFER 1024

int httpClient_get(const char* url, char* resp);
int httpClient_get_with_json(const char* url, const char* json_data, char* resp);

#endif