#ifndef HEADER_HTTPCLIENT_H
#define HEADER_HTTPCLIENT_H

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "sdkconfig.h"
#include "wifi.h"

void httpClient_main();

#endif