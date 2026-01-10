#include "logging.h"
#include "esp_log.h"
#include <stdarg.h>
#include <stdio.h>

#define LOG_BUF_SIZE 256

void log_msg_info(const char *tag, const char *fmt, ...)
{
    char buf[LOG_BUF_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    ESP_LOGI(tag, "%s", buf);
}

void log_msg_warn(const char *tag, const char *fmt, ...)
{
    char buf[LOG_BUF_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    ESP_LOGW(tag, "%s", buf);
}

void log_msg_error(const char *tag, const char *fmt, ...)
{
    char buf[LOG_BUF_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    ESP_LOGE(tag, "%s", buf);
}
