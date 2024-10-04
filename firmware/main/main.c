/* SPI Master example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "esp_log.h"
#include "matrix.h"
#include "led_driver.h"
#include "wifi_time.h"


void app_main(void)
{
    init_display();
    // vTaskDelay(200);
    // set_frame_display(screen);
    set_matrix_hours(27);
    wifi_init();
    sntp_time_init();
    time_t now = 0;
    struct tm timeinfo = { 0 };
    while(1){
    time(&now);
    localtime_r(&now, &timeinfo);
    char strftime_buf[64];
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    char* st = &strftime_buf[11];
    ESP_LOGW("main", "The current date/time: %s", st);
    display_time((uint8_t*)st);
    vTaskDelay(1000/portTICK_PERIOD_MS);

    }
}
