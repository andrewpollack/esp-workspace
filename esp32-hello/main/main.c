#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "logging.h"

void app_main(void)
{
    log_info("esp32-hello", "Starting up");

    int count = 0;
    while (1) {
        log_info("esp32-hello", "Hello world! Count: %d", count++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
