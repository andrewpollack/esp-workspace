# Load secrets from repo root
set(SECRETS_FILE "${CMAKE_CURRENT_LIST_DIR}/../../secrets.cmake")
if(EXISTS ${SECRETS_FILE})
    include(${SECRETS_FILE})
else()
    message(WARNING "secrets.cmake not found. Copy secrets.cmake.example and set your credentials.")
    set(WIFI_SSID "unconfigured")
    set(WIFI_PASSWORD "unconfigured")
endif()

idf_component_register(
    SRCS "wifi.c"
    INCLUDE_DIRS "include"
    REQUIRES log esp_wifi esp_netif esp_event nvs_flash logging
)

# Pass credentials as compile definitions
target_compile_definitions(${COMPONENT_LIB} PRIVATE
    WIFI_SSID="${WIFI_SSID}"
    WIFI_PASSWORD="${WIFI_PASSWORD}"
)
