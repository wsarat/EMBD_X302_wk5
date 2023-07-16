#ifndef HEADER_HTTPSERVER_H
#define HEADER_HTTPSERVER_H

#include "esp_tls.h"
#include "esp_http_server.h"
#include "wifi.h"

#define ASYNC_WORKER_TASK_PRIORITY      5
#define ASYNC_WORKER_TASK_STACK_SIZE    2048
#define MAX_ASYNC_REQUESTS              2

//esp_err_t httpd_req_async_handler_begin(httpd_req_t *r, httpd_req_t **out);
//esp_err_t httpd_req_async_handler_complete(httpd_req_t *r);

void httpServer_init(void);

#endif