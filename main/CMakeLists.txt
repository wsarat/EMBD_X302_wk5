idf_component_register(SRCS "misc.c" "httpServer.c" "httpClient.c" "wifi.c" "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES ${requires}
                    EMBED_TXTFILES "certs/servercert.pem"
                                   "certs/prvtkey.pem"
                                   "web/page1.html")
