#include "matrix.h"

void addNumber(uint16_t *screen,uint8_t num, bool size)
{
    if (size)
    {
        for (uint8_t i = 0; i < 7; i++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                screen[i] ^= (0x01 & (numberBig[num][j] >> i));
                screen[i] = screen[i] << 1;
            }
            screen[i] = screen[i] << 1;
        }
    }
    else
    {
        for (uint8_t i = 0; i < 7; i++)
        {
            for (uint8_t j = 0; j < 3; j++)
            {
                screen[i] ^= (0x01 & (numberSmall[num][j] >> i));
                screen[i] = screen[i] << 1;
            }
            screen[i] = screen[i] << 1;
        }
    }
}

void addSpace(uint16_t *screen, int8_t spaces)
{
    if (spaces > 0)
    {
        for (uint8_t i = 0; i < 7; i++)
            screen[i] = screen[i] << spaces;
    }
    else
    {
        spaces = abs(spaces);
        for (uint8_t i = 0; i < 7; i++)
            screen[i] = screen[i] >> spaces;
    }
}

void set_matrix_hours(uint8_t hour)
{
    uint8_t digit[2];
    if (hour >= 10)
    {
        digit[1] = hour / 10;
        digit[0] = hour % 10;
    }
    else
    {
        digit[1] = 0;
        digit[0] = hour;
    }

    uint16_t pixel_bytes[7] = {0};

    for (int8_t k = 0; k < 2; k++)
        for (uint8_t i = 0; i < 7; i++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                pixel_bytes[i] ^= (0x01 & (numberBig[digit[k]][j] >> i));
                pixel_bytes[i] = pixel_bytes[i]<< 1;
            }
            if (!k)
                pixel_bytes[i] = pixel_bytes[i] << 1;
        }

    led_matrix_set(2,(uint8_t*)pixel_bytes);


}
void display_time(uint8_t* time_str){
    uint16_t disp[7]={0};
    addNumber(disp,time_str[1]-48,1);    
    addNumber(disp,time_str[0]-48,1);   
    addSpace(disp,-1); 
    ESP_LOGI("SD","prinmt %d",time_str[1]-48);
    led_matrix_set(2,(uint8_t*)disp);
    addNumber(disp,time_str[4]-48,1);    
    addNumber(disp,time_str[3]-48,1);
    led_matrix_set(1,(uint8_t*)disp);
    addSpace(disp,1); 
    addNumber(disp,time_str[7]-48,0);    
    addNumber(disp,time_str[6]-48,0);    
    led_matrix_set(0,(uint8_t*)disp);
}

void set_frame_display(uint32_t *scr_data)
{
    uint32_t screen[7] = {0}; //{0xffffffff,0x0f0f0f0f,0x0f0f0f0f,0x0f0f0f0f,0x0f0f0f0f,0x0f0f0f0f,0x55555555};
    uint8_t pixel_byte[14] = {0};
    uint32_t data[7];

    // addNumber(6, 0);
    // addNumber(7, 0);
    // addNumber(5, 1);
    // addNumber(1, 1);
    // addSpace(2);
    // addNumber(9, 1);
    // addNumber(2, 1);
    // addSpace(-1);

    // uint8_t pixel_byte[14] = {0x55,1,0x05,0xff,0x55,0xff,0x55,0xff,0x55,0xff,0x55,0xff,0x55,0xff};
    while (1)
    {
        /* code */
        memcpy(data, scr_data, 28);

        for (int i = 2; i >= 0; i--)
        {
            // spi_device_acquire_bus(spi[i], portMAX_DELAY);

            for (int j = 0; j < 14; j += 2)
            {
                *(uint16_t *)&pixel_byte[j] = data[j / 2];
                data[j / 2] = data[j / 2] >> 11;
                // printf("num %d %X  %X num j \n",i, pixel_byte[j],pixel_byte[j+1]);
            }

            // send_data(spi[i], TM16XX_CMD_DATA_AUTO, 0, NULL, 0);
            // vTaskDelay(1 / 1000);
            // send_data(spi[i], 0xc0, 0xff, pixel_byte, 14);
            // spi_device_release_bus(spi[i]);
            led_matrix_set(i,pixel_byte);

        }
        for (int i = 0; i < 7; i++)
        {
            screen[i] = ((bool)(screen[i] & 0x80000000)) + (screen[i] << 1);
        }
        vTaskDelay(10);
    }
}