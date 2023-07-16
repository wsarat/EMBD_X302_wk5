idf_component_register(SRCS "httpServer.c" "httpClient.c" "wifi.c" "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES ${requires})
