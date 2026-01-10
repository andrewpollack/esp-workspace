#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_http_server.h"
#include "mdns.h"
#include "logging.h"
#include "wifi.h"

#define TAG "main"

static void mdns_init_service(void)
{
    ESP_ERROR_CHECK(mdns_init());
    ESP_ERROR_CHECK(mdns_hostname_set(MDNS_HOSTNAME));
    ESP_ERROR_CHECK(mdns_instance_name_set("ESP32 WiFi Device"));
    ESP_ERROR_CHECK(mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0));
    log_info(TAG, "mDNS hostname: %s.local", MDNS_HOSTNAME);
}

static esp_err_t root_handler(httpd_req_t *req)
{
    esp_netif_ip_info_t *ip = wifi_get_ip_info();
    char ip_str[16] = "0.0.0.0";
    if (ip) {
        snprintf(ip_str, sizeof(ip_str), IPSTR, IP2STR(&ip->ip));
    }
    char resp[512];
    snprintf(resp, sizeof(resp),
        "<!DOCTYPE html><html><head><title>ESP32</title></head>"
        "<body><h1>ESP32 WiFi</h1>"
        "<p>IP: %s</p>"
        "<p>Heap: %lu bytes free</p>"
        "<p><a href=\"/status\">/status</a> - JSON API</p>"
        "</body></html>",
        ip_str,
        (unsigned long)esp_get_free_heap_size());
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t status_handler(httpd_req_t *req)
{
    esp_netif_ip_info_t *ip = wifi_get_ip_info();
    char ip_str[16] = "0.0.0.0";
    if (ip) {
        snprintf(ip_str, sizeof(ip_str), IPSTR, IP2STR(&ip->ip));
    }
    char resp[128];
    snprintf(resp, sizeof(resp), "{\"status\":\"ok\",\"heap\":%lu,\"ip\":\"%s\"}",
             (unsigned long)esp_get_free_heap_size(), ip_str);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t root = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = root_handler,
        };
        httpd_uri_t status = {
            .uri = "/status",
            .method = HTTP_GET,
            .handler = status_handler,
        };
        httpd_register_uri_handler(server, &root);
        httpd_register_uri_handler(server, &status);
        log_info(TAG, "HTTP server started on port 80");
    }
    return server;
}

void app_main(void)
{
    log_info(TAG, "Starting...");

    if (wifi_init_sta() != ESP_OK) {
        log_error(TAG, "WiFi init failed");
        return;
    }

    mdns_init_service();
    start_webserver();

    log_info(TAG, "Ready! Access at http://%s.local", MDNS_HOSTNAME);
}
