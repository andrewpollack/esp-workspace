#pragma once

#include "esp_err.h"
#include "esp_netif.h"

/**
 * Initialize WiFi in station mode and connect.
 * Blocks until connected or max retries exceeded.
 * Credentials are injected at build time from secrets.cmake.
 *
 * @return ESP_OK on success, ESP_FAIL on connection failure
 */
esp_err_t wifi_init_sta(void);

/**
 * Get the current IP address.
 * Only valid after successful wifi_init_sta().
 *
 * @return IP info or NULL if not connected
 */
esp_netif_ip_info_t *wifi_get_ip_info(void);
