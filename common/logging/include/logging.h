#pragma once

#define log_info(tag, fmt, ...) log_msg_info(tag, fmt, ##__VA_ARGS__)
#define log_warn(tag, fmt, ...) log_msg_warn(tag, fmt, ##__VA_ARGS__)
#define log_error(tag, fmt, ...) log_msg_error(tag, fmt, ##__VA_ARGS__)

void log_msg_info(const char *tag, const char *fmt, ...);
void log_msg_warn(const char *tag, const char *fmt, ...);
void log_msg_error(const char *tag, const char *fmt, ...);
