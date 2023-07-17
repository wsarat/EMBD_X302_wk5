idf_component_register(SRCS "ds18b20_lowlevel.c" "misc.c" "httpServer.c" "httpClient.c" "wifi.c" "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES ${requires}
                    EMBED_TXTFILES "certs/servercert.pem"
                                   "certs/prvtkey.pem"
                                   "web/page1.html")
