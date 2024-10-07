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

void addCharFull(uint64_t *screen, uint8_t character, bool size)
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
    case 'm' - ASCII_OFFSET:
    case 'v' - ASCII_OFFSET:
    case 'w' - ASCII_OFFSET:
    case '~' - ASCII_OFFSET:
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
uint8_t addCharArray(uint8_t *screen, uint8_t character)
{
    uint8_t cnt = 0;
    character -= ASCII_OFFSET;
    switch (character)
    {
    case 'M' - ASCII_OFFSET:
    case 'T' - ASCII_OFFSET:
    case 'V' - ASCII_OFFSET:
    case 'W' - ASCII_OFFSET:
    case 'X' - ASCII_OFFSET:
    case 'Y' - ASCII_OFFSET:
    case 'm' - ASCII_OFFSET:
    case 'v' - ASCII_OFFSET:
    case 'w' - ASCII_OFFSET:
    case '~' - ASCII_OFFSET:
    {
        //     for (uint8_t i = 0; i < 4; i++)
        //     {
        //         if (!ASCII[character][3 - i])
        //             continue;
        //         screen[3 - i] = ASCII[character][3 - i];
        //     }
        //     screen[i] = ASCII[character][3];
        //     i++;
        //     screen[i] = 0;
        //     if (!ASCII[character][0])
        //         break;
        screen[0] = ASCII[character][0];
        screen[1] = ASCII[character][3];
        screen[2] = ASCII[character][2];
        screen[3] = ASCII[character][1];
        screen[4] = ASCII[character][0];
        cnt = 5;
        // screen[cnt+=1] = ASCII[character][0];
        // for (int8_t i = 3; i >= 0; i--)
        // {
        // printf("%d\n",i);
        // if (!ASCII[character][i])
        //     continue;
        // screen[cnt] = ASCII[character][i];
        //     cnt++;
        // }
        break;
    }
    default:
        for (int8_t i = 3; i >= 0; i--)
        {
            if (!ASCII[character][i])
                continue;
            screen[cnt] = ASCII[character][i];
            cnt++;
        }

        // i=0;
        // while(ASCII[character][i])
        // {
        //     screen[i] = ASCII[character][i];
        //     i++;
        //     // ASCII[character]++;
        // }
        // i=3-i;
        // for (i = 0; i < 4; i++)
        // {
        //     if (!ASCII[character][3-i])
        //          continue;
        //     screen[i] = ASCII[character][3-i];
        // }
        // // screen[i] = ASCII[character][i];
        // // i++;
        // screen[i] = 0;
        // // screen[0] = ASCII[character][3];
        // // screen[1] = ASCII[character][2];
        // // screen[2] = ASCII[character][1];
        // // screen[3] = ASCII[character][0];
        // // screen[4] =  ASCII[character][0];
        // // i = 4;
        break;
    }
    return cnt + 1;
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

void set_frame_arr(uint8_t *scr_data, uint8_t len)
{
    uint8_t pixel_byte[14] = {0};
    for (int i = 2; i >= 0; i--)
    {
        for (uint8_t k = 0; k < 7; k++)
        {
            uint32_t tempSeg = *(uint16_t *)&pixel_byte[k * 2];
            for (int j = 0; j < 11; j++)
            {
                tempSeg |= ((scr_data[j] & (0x01 << k)) << j);
            }
            *(uint16_t *)&pixel_byte[k * 2] = (uint16_t)(tempSeg >> k);
        }
        led_matrix_set(i, pixel_byte);

        memset(pixel_byte, 0, 14);
        scr_data += 11;
    }
}

void displayText(char *text)
{
    // char *tmp = text;
    size_t len = strlen(text);
    ESP_LOGW("b", " str len %d ", len);
    if (len * 5 < 33)
        len = 33;
    else
        len = len * 5;

    uint8_t *disp = (uint8_t *)calloc(len, sizeof(uint8_t));
    uint8_t addlen = 0;
    // uint8_t **disp
    while (*text)
    {
        addlen += addCharArray(&disp[addlen], *text);
        text++;
    }

    // for (uint16_t i = 0; i < 40; i++)
    // {
    //     printf("%X \t", disp[i]);
    // }
    // printf(" \n");
    for (uint8_t i = 0; i < 1; i++)
    {
        set_frame_arr(&disp[i], addlen);
        vTaskDelay(100);
    }
}

void set_frame_display(uint64_t *scr_data /*, uint8_t timeout*/)
{
    uint8_t pixel_byte[14] = {0};
    uint64_t data[7];
    while (1)
    {
        memcpy(data, scr_data, 56);

        for (int i = 2; i >= 0; i--)
        {

            for (int j = 0; j < 14; j += 2)
            {
                *(uint32_t *)&pixel_byte[j] = data[j / 2];
                data[j / 2] = data[j / 2] >> 11;
            }

            led_matrix_set(i, pixel_byte);
        }
        for (int i = 0; i < 7; i++)
        {
            scr_data[i] = ((bool)(scr_data[i] & 0x8000000000000000)) + (scr_data[i] << 1);
        }
        vTaskDelay(10);
    }
}

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
        ESP_LOGE("display", "errr %X", chCnt);
        break;
    }
}

void displayTimeAni(uint8_t hour, uint8_t minute, uint8_t second)
{
    uint8_t chCnt = 0;
    static uint8_t timeTmp[6] = {99, 99, 99, 99, 99, 99};
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
            chCnt |= (0x01 << i);
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
            chCnt |= (0x01 << i);
        }
        else
        {
            for (uint8_t j = 0; j < 3; j++)
                rollingDigit[i][j] = numberSmall[time[i]][j];
            // chCnt<<=1;
        }
    }
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

void displayTextOld(char *text)
{
    char *tmp = text;
    uint64_t disp[7] = {0};

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
    // addSpaceFull(disp, -2);

    set_frame_display(disp);
}

void displayTextLoop(char *text)
{
    // char *tmp = text;
    size_t len = strlen(text);
    if (len * 5 < 33)
        len = 33;
    else
        len = len * 5;
    ESP_LOGI("b", " str len %d ", len);

    // uint8_t *disp = (uint8_t *)calloc(len, sizeof(uint8_t));
    uint8_t disp[183] ={0};
    uint8_t addlen = 33;
    // uint8_t **disp
    while (*text)
    {
        addlen += addCharArray(&disp[addlen], *text);
        text++;
    }

    int i = 0;
    while (1)
    {
        set_frame_arr(&disp[i], addlen);
        vTaskDelay(10);
        i++;
        if (i == 183/*(len-33)*/)
            i = 0;
    }

}
