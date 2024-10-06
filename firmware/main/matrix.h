#pragma once
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"led_driver.h"
#include"font.h"
#include "esp_log.h"

#define ASCII_OFFSET 32
#ifdef __cplusplus
extern "C" {
#endif

void addNumber(uint16_t *screen,uint8_t num, bool size);
void addSpace(uint16_t *screen, int8_t spaces);
void set_matrix_hours(uint8_t hour);
void set_frame_display(uint64_t *scr_data);

void displayText(char* text);

void display_time(uint8_t* time_str);
void displayTimeAni(uint8_t hour, uint8_t minute, uint8_t second);
void displayTextOld(char *text);
void displayTextLoop(char *text);

#ifdef __cplusplus
}
#endif
#endif
