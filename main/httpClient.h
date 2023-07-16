#ifndef HEADER_HTTPCLIENT_H
#define HEADER_HTTPCLIENT_H

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "sdkconfig.h"

#include "esp_tls.h"
#include "esp_http_client.h"

#include "wifi.h"
#include "esp_http_client.h"

#include <string.h>
#include <sys/param.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_HTTP_RECV_BUFFER 512
#define MAX_HTTP_OUTPUT_BUFFER 1024

int httpClient_get(const char* url, const char* query, char* resp);

#endif