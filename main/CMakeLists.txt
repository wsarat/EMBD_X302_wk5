idf_component_register(SRCS "httpServer.c" "httpClient.c" "wifi.c" "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES ${requires}
                    EMBED_TXTFILES "certs/servercert.pem"
                                   "certs/prvtkey.pem")
