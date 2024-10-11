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

TaskHandle_t dispTask = NULL;
extern EventGroupHandle_t s_ping_event_group;

static void disp_task(void *arg)
{
    displayTextLoop("Connecting to Internet, syncing time !");
    vTaskDelete(NULL);
}

void app_main(void)
{
    init_display();
    // set_frame_display(screen);
    xTaskCreate(disp_task, "disp_task", 1024 * 2, NULL, 10, &dispTask);

    // displayText("Hello");

    wifi_init();
    sntp_time_init();
    initialize_ping();
    time_t now = 0;
    struct tm timeinfo = {0};
    // TickType_t xLastWakeTime = xTaskGetTickCount();
    if (dispTask)
        vTaskDelete(dispTask);
    uint8_t sec = 99;
    bool cleared = 0;
    uint16_t tmpTime = 0;
    clear_led_matrix();
    while (1)
    {
        time(&now);
        localtime_r(&now, &timeinfo);
        // if ((timeinfo.tm_min - tmpMin )> 2)
        if (((uint16_t)now - tmpTime )> 15*60)
        {
            // xEventGroupWaitBits(s_ping_event_group, PING_OK_BIT, pdTRUE, pdFALSE, 0);
            ping_start();
            // tmpMin = timeinfo.tm_min;
            tmpTime = (uint16_t)now;

        }
        vTaskDelay(100 / portTICK_PERIOD_MS);

        if (!(xEventGroupWaitBits(s_ping_event_group,
                                  PING_OK_BIT,
                                  pdFALSE,
                                  pdFALSE,
                                  0) &
              PING_OK_BIT))
        {
            // ESP_LOGW("led","%d ", cleared);
            if (cleared == 0)
            {
                clear_led_matrix();
                cleared = 1;
            }
            continue;
        }
        cleared = 0;

        // char strftime_buf[64];?
        // strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
        // char* st = &strftime_buf[11];
        // ESP_LOGW("main", "The current date/time: %s %d",st, timeinfo.tm_min );
        // display_time((uint8_t*)st);
        if (sec != timeinfo.tm_sec)
        {
            sec = timeinfo.tm_sec;
            displayTimeAni(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

        }
        // displayTimeAni(hour+=1,min+=1,sec+=1);
    }
}
