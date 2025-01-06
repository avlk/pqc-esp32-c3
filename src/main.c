#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include <wolfssl/wolfcrypt/settings.h>
#ifdef WOLFSSL_ESPIDF
    #include <esp_log.h>
    #include <rtc_wdt.h>
    #include <wolfssl/wolfcrypt/port/Espressif/esp32-crypt.h>
#endif

#include <wolfssl/version.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfcrypt/benchmark/benchmark.h>

#define TAG "wolfSSL demo"

#define BLINK_GPIO 8
#define BLINK_PERIOD 200
static uint8_t s_led_state = 0;

static void blink_led(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, s_led_state);
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}


void app_main() {
    /* Configure the peripheral according to the LED type */
    configure_led();

    printf("\nHello World wolfSSL Version %s\n", LIBWOLFSSL_VERSION_STRING);

#if defined(HAVE_VERSION_EXTENDED_INFO) && defined(WOLFSSL_ESPIDF)
    esp_ShowExtendedSystemInfo();
#endif
    int ret =  benchmark_test(NULL);
    printf("\nbenchmark_test complete! result code: %d\n", ret);

    while (1) {
        printf("Benchmark complete, LED %s\n", s_led_state == true ? "ON" : "OFF");
        blink_led();
        /* Toggle the LED state */
        s_led_state = !s_led_state;
        vTaskDelay(BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
