idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES logging wifi esp_http_server
)
