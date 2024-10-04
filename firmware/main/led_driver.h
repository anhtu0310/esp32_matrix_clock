#pragma once
#ifndef _LED_DRIVER_H_
#define _LED_DRIVER_H_

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

#define LED_HOST    SPI2_HOST


#define PIN_NUM_MOSI  7
#define PIN_NUM_CLK   8
#define PIN_NUM_CS0   9
#define PIN_NUM_CS1   6
#define PIN_NUM_CS2   5

#define TM16XX_CMD_DATA_AUTO  0x40
#define TM16XX_CMD_DATA_READ  0x42			// command to read data used on two wire interfaces of TM1637
#define TM16XX_CMD_DATA_FIXED 0x44
#define TM16XX_CMD_DISPLAY    0x80
#define TM16XX_CMD_ADDRESS    0xC0



void send_data(spi_device_handle_t spi, uint8_t cmd, uint8_t address, uint8_t *data, uint8_t size);
void init_led(spi_device_handle_t spi, bool displayOn, uint8_t brightness);
void clear_led(spi_device_handle_t spi);
void all_led(spi_device_handle_t spi);
esp_err_t led_matrix_set(uint8_t disp_id, uint8_t* payload);
void init_led_matrix();
esp_err_t init_display();


#ifdef __cplusplus
}
#endif

#endif
