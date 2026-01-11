#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "logging.h"

#define TAG "led"
#define LED_PIN GPIO_NUM_26

void app_main(void)
{
    log_info(TAG, "Configuring LED on GPIO %d", LED_PIN);

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&io_conf);

    while (1) {
        gpio_set_level(LED_PIN, 1);
        log_info(TAG, "LED ON");
        vTaskDelay(pdMS_TO_TICKS(1000));

        gpio_set_level(LED_PIN, 0);
        log_info(TAG, "LED OFF");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
