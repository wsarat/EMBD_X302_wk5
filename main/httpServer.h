#ifndef HEADER_HTTPSERVER_H
#define HEADER_HTTPSERVER_H

#include "esp_tls.h"
#include <esp_https_server.h>
#include "wifi.h"
#include "misc.h"
#include <pthread.h>

void httpServer_init(void);
void httpServer_start();
void httpServer_stop();

#endif