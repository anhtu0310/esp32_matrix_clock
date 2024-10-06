#include "matrix.h"

void addNumber(uint16_t *screen, uint8_t num, bool size)
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
void addRaw(uint16_t *screen, uint8_t *data, uint8_t lines)
{
    for (uint8_t i = 0; i < 7; i++)
    {
        for (uint8_t j = 0; j < lines; j++)
        {
            screen[i] ^= (0x01 & (data[j] >> i));
            screen[i] = screen[i] << 1;
        }
        screen[i] = screen[i] << 1;
    }
}

void addRawU16(uint16_t *screen, uint16_t *data, uint8_t lines)
{
    for (uint8_t i = 0; i < 7; i++)
    {
        for (uint8_t j = 0; j < lines; j++)
        {
            screen[i] ^= (0x01 & (data[j] >> i));
            screen[i] = screen[i] << 1;
        }
        screen[i] = screen[i] << 1;
    }
}

void addCharFull(uint32_t *screen, uint8_t character, bool size)
{
    character -= ASCII_OFFSET;
    switch (character)
    {
    case 'M' - ASCII_OFFSET:
    case 'T' - ASCII_OFFSET:
    case 'V' - ASCII_OFFSET:
    case 'W' - ASCII_OFFSET:
    case 'X' - ASCII_OFFSET:
    case 'Y' - ASCII_OFFSET:
        for (uint8_t i = 0; i < 7; i++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                if (!ASCII[character][j])
                    break;
                screen[i] ^= (0x01 & (ASCII[character][j] >> i));
                screen[i] = screen[i] << 1;
            }
            screen[i] ^= (0x01 & (ASCII[character][0] >> i));
            screen[i] = screen[i] << 1;
            screen[i] = screen[i] << 1;
        }
        break;

    default:
        for (uint8_t i = 0; i < 7; i++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                if (!ASCII[character][j])
                    break;
                screen[i] ^= (0x01 & (ASCII[character][j] >> i));
                screen[i] = screen[i] << 1;
            }
            screen[i] = screen[i] << 1;
        }
        break;
    }
}

void addChar(uint16_t *screen, uint8_t character)
{
    character -= ASCII_OFFSET;
    switch (character)
    {
    case 'M' - ASCII_OFFSET:
    case 'T' - ASCII_OFFSET:
    case 'V' - ASCII_OFFSET:
    case 'W' - ASCII_OFFSET:
    case 'X' - ASCII_OFFSET:
    case 'Y' - ASCII_OFFSET:
        for (uint8_t i = 0; i < 7; i++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                if (!ASCII[character][j])
                    break;
                screen[i] ^= (0x01 & (ASCII[character][j] >> i));
                screen[i] = screen[i] << 1;
            }
            screen[i] ^= (0x01 & (ASCII[character][0] >> i));
            screen[i] = screen[i] << 1;
            screen[i] = screen[i] << 1;
        }
        break;

    default:
        for (uint8_t i = 0; i < 7; i++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                if (!ASCII[character][j])
                    break;
                screen[i] ^= (0x01 & (ASCII[character][j] >> i));
                screen[i] = screen[i] << 1;
            }
            screen[i] = screen[i] << 1;
        }
        break;
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

void addSpaceFull(uint32_t *screen, int8_t spaces)
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
                pixel_bytes[i] = pixel_bytes[i] << 1;
            }
            if (!k)
                pixel_bytes[i] = pixel_bytes[i] << 1;
        }

    led_matrix_set(2, (uint8_t *)pixel_bytes);
}
void display_time(uint8_t *time_str)
{
    uint16_t disp[7] = {0};

    addNumber(disp, time_str[1] - 48, 1);
    addNumber(disp, time_str[0] - 48, 1);
    addSpace(disp, -1);

    led_matrix_set(2, (uint8_t *)disp);
    // addChar(disp,':');

    addNumber(disp, time_str[4] - 48, 1);
    addNumber(disp, time_str[3] - 48, 1);
    addChar(disp, ':');
    addSpace(disp, -2);

    led_matrix_set(1, (uint8_t *)disp);

    addSpace(disp, 3);
    addNumber(disp, time_str[7] - 48, 0);
    addNumber(disp, time_str[6] - 48, 0);
    addChar(disp, ':');

    addSpace(disp, -1);

    led_matrix_set(0, (uint8_t *)disp);
}

void displayText(char *text)
{
    char *tmp = text;
    uint32_t disp[7] = {0};

    while (*text)
    {
        // addCharFull(disp,*text,1);
        text++;
    }
    while (text != tmp)
    {
        text--;
        addCharFull(disp, *text, 1);
    }
    addSpaceFull(disp, -2);

    set_frame_display(disp);
}

void set_frame_display(uint32_t *scr_data)
{
    // uint32_t screen[7] = {0}; //{0xffffffff,0x0f0f0f0f,0x0f0f0f0f,0x0f0f0f0f,0x0f0f0f0f,0x0f0f0f0f,0x55555555};
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
    // while (1)
    // {
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
        led_matrix_set(i, pixel_byte);
    }
    // for (int i = 0; i < 7; i++)
    // {
    //     screen[i] = ((bool)(screen[i] & 0x80000000)) + (screen[i] << 1);
    // }
    // vTaskDelay(10);
    // }
}

// void rollAni(uint8_t num){
//     static last
// }
void displayRaw(uint16_t (*rollingDigit)[4], uint8_t chCnt)
{
    uint16_t disp[7] = {0};

    switch (chCnt)
    {
    case 0b00111111:
    case 0b00111110:
        addRawU16(disp, rollingDigit[1], 4);
        addRawU16(disp, rollingDigit[0], 4);
        addSpace(disp, -1);
        led_matrix_set(2, (uint8_t *)disp);
    case 0b00111100:
    case 0b00111000:
        addRawU16(disp, rollingDigit[3], 4);
        addRawU16(disp, rollingDigit[2], 4);
        addChar(disp, ':');
        addSpace(disp, -2);
        led_matrix_set(1, (uint8_t *)disp);
    case 0b00110000:
    case 0b00100000:
        addSpace(disp, 3);
        // addNumber(disp, time_str[7] - 48, 0);
        addRawU16(disp, rollingDigit[5], 3);
        addRawU16(disp, rollingDigit[4], 3);
        addChar(disp, ':');
        addSpace(disp, -1);
        led_matrix_set(0, (uint8_t *)disp);
        break;
    default:
        ESP_LOGE("display", "errr %X",chCnt);
        break;
    }
    // addNumber(disp, time_str[1] - 48, 1);
    // addNumber(disp, time_str[0] - 48, 1);

    // addChar(disp,':');
}

void displayTimeAni(uint8_t hour, uint8_t minute, uint8_t second)
{
    // static uint8_t tmpHour = 0;
    // static uint8_t tmpSec = 0;
    // static uint8_t tmpMin = 0;
    uint8_t chCnt = 0;
    // if(tmpHour != hour) chCnt = 3;
    // else if (tmpMin != minute) chCnt = 2;
    // else if (tmpSec != second) chCnt = 1;
    static uint8_t timeTmp[6] = {99,99,99,99,99,99};
    uint8_t time[6];
    time[0] = hour / 10;
    time[1] = hour % 10;
    time[2] = minute / 10;
    time[3] = minute % 10;
    time[4] = second / 10;
    time[5] = second % 10;

    uint16_t rollingDigit[6][4];

    for (uint8_t i = 0; i < 4; i++)
    {
        if (time[i] != timeTmp[i])
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                rollingDigit[i][j] = (numberBig[timeTmp[i]][j] | (numberBig[time[i]][j] << 7)) >> 1;
            }
            timeTmp[i] = time[i];
            chCnt |= (0x01<<i);
        }
        else
        {
            for (uint8_t j = 0; j < 4; j++)
                rollingDigit[i][j] = numberBig[time[i]][j];
            // chCnt<<=1;
        }
    }
    for (uint8_t i = 4; i < 6; i++)
    {
        if (time[i] != timeTmp[i])
        {
            for (uint8_t j = 0; j < 3; j++)
            {
                rollingDigit[i][j] = (numberSmall[timeTmp[i]][j] | (numberSmall[time[i]][j] << 5)) >> 1;
            }
            timeTmp[i] = time[i];
            chCnt |= (0x01<<i);
        }
        else
        {
            for (uint8_t j = 0; j < 3; j++)
                rollingDigit[i][j] = numberSmall[time[i]][j];
            // chCnt<<=1;
        
        }
    }

    // for (uint8_t i = 0; i < 3; i++)
    // {
    //     rollingDigit[i] = (numberSmall[tmpS][i] | (numberSmall[time_str[7] - 48][i] << 5)) >> 1;
    // }
    // if (tmpS != (time_str[7] - 48))
    // {
    //     tmpS = time_str[7] - 48;
    // }
    // ESP_LOGI("SE", " %d %X %X %X", tmpS, rollingDigit[0], rollingDigit[1], rollingDigit[2]);
    // uint8_t shift_len
    for (uint8_t i = 0; i < 7; i++)
    {
        displayRaw(rollingDigit, chCnt);
        for (uint8_t k = 0; k < 4; k++)
            if ((rollingDigit[k][1] | rollingDigit[k][3]) > 0x7F)
                for (uint8_t j = 0; j < 4; j++)
                {
                    rollingDigit[k][j] = (rollingDigit[k][j] >> 1);
                }
        if (i < 5)
            for (uint8_t k = 4; k < 6; k++)
                if ((rollingDigit[k][0] | rollingDigit[k][1]) > 0x7F)
                    for (uint8_t j = 0; j < 3; j++)
                    {

                        rollingDigit[k][j] = (rollingDigit[k][j] >> 1) & 0xFFFC;
                    }

        vTaskDelay(5);
    }
}
