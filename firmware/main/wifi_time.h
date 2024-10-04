#pragma once
#ifndef _WIFIT_H_
#define _WIFIT_H_


#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include <time.h>
#include <sys/time.h>
#include "esp_netif_sntp.h"
// #include "lwip/ip_addr.h"
#include "esp_sntp.h"

#define EXAMPLE_ESP_WIFI_SSID      "FPT Telecom-3F60"
#define EXAMPLE_ESP_WIFI_PASS      "123456788"
#define EXAMPLE_ESP_MAXIMUM_RETRY  5
void wifi_init(void);

void sntp_time_init(void);

#endif