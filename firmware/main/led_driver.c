#include "led_driver.h"

spi_device_handle_t spi[3];
const uint8_t cs_pins[3] = {PIN_NUM_CS0,PIN_NUM_CS1,PIN_NUM_CS2};

void send_data(spi_device_handle_t spi, uint8_t cmd, uint8_t address, uint8_t *data, uint8_t size)
{

    static spi_transaction_t trans;
    memset(&trans, 0, sizeof(spi_transaction_t));
    if (cmd)
        trans.cmd = cmd;
    if (address)
        trans.addr = address;

    // if(size)
    // {
    //     trans.flags=SPI_TRANS_USE_TXDATA;
    // }
    // else
    // {
    //     trans.flags=0;
    // }
    trans.length = size * 8;
    trans.tx_buffer = data;
    esp_err_t ret = spi_device_queue_trans(spi, &trans, portMAX_DELAY);
    assert(ret == ESP_OK);
}

void init_led(spi_device_handle_t spi, bool displayOn, uint8_t brightness)
{
    send_data(spi, 3, 0, NULL, 0);
    if (brightness > 7)
        brightness = 7;
    send_data(spi, TM16XX_CMD_DISPLAY | displayOn << 3 | brightness, 0, NULL, 0);
}

void clear_led(spi_device_handle_t spi)
{
    uint8_t data[14] = {0};
    // data[0] = {}
    // send_data(spi,TM16XX_CMD_DATA_AUTO, TM16XX_CMD_ADDRESS,data,14);
    // send_data(spi,TM16XX_CMD_DATA_AUTO, 0,NULL,0);
    send_data(spi, TM16XX_CMD_DATA_AUTO, TM16XX_CMD_ADDRESS, data, 14);
}

void all_led(spi_device_handle_t spi)
{
    uint8_t data[14] = {0};
    // data[0] =0x55;
    // data[1] = 0xff;
    for (int8_t i = 0; i < 14; i++)
        data[i] = 0xff;
    // send_data(spi,TM16XX_CMD_DATA_AUTO, 0,NULL,0);

    send_data(spi, TM16XX_CMD_DATA_AUTO, TM16XX_CMD_ADDRESS, data, 14);
}

esp_err_t led_matrix_set(uint8_t disp_id, uint8_t* payload)
{
    if (disp_id > 2)
        return -1;
    else
    {
        spi_device_acquire_bus(spi[disp_id], portMAX_DELAY);
        send_data(spi[disp_id], TM16XX_CMD_DATA_AUTO, 0, NULL, 0);
        vTaskDelay(1 / 1000);
        send_data(spi[disp_id], TM16XX_CMD_ADDRESS, 0xff, payload, 14);
        spi_device_release_bus(spi[disp_id]);

    }
    return ESP_OK;
}

void init_led_matrix()
{
    for (int i = 0; i < 3; i++)
    {
        spi_device_acquire_bus(spi[i], portMAX_DELAY);
        clear_led(spi[i]);
        vTaskDelay(1);
        init_led(spi[i], 1, 0);
        // vTaskDelay(1);
        // all_led(spi[i]);
        // vTaskDelay(50);
        // clear_led(spi[i]);
        spi_device_release_bus(spi[i]);
    }
}

esp_err_t init_display()
{
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .miso_io_num = -1,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        // .max_transfer_sz=PARALLEL_LINES*320*2+8
    };

    // spi_device_interface_config_t devcfg[3];
    // for (int i=0; i<3; i++){
    //     devcfg[i].clock_source     = SPI_CLK_SRC_DEFAULT; //SOC_MOD_CLK_APB;
    //     devcfg[i].clock_speed_hz=500*1000;           //Clock out at 10 MHz
    //     devcfg[i].mode=3;                                //SPI mode 0
    //     devcfg[i].command_bits = 8;
    //     devcfg[i].address_bits = 8;
    //     devcfg[i].spics_io_num=cs_pins[i];               //CS pin
    //     devcfg[i].queue_size=8;                          //We want to be able to queue 7 transactions at a time
    //     devcfg[i].flags = SPI_DEVICE_TXBIT_LSBFIRST;
    //         // .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line

    // }

    // Initialize the SPI bus
    ret = spi_bus_initialize(LED_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    // Attach the LCD to the SPI bus
    for (int i = 0; i < 3; i++)
    {

        spi_device_interface_config_t devcfg = {

            .clock_speed_hz = 2000 * 1000, // Clock out at 10 MHz
            .mode = 3,                     // SPI mode 0
            .command_bits = 8,
            // .address_bits = 8,
            .spics_io_num = cs_pins[i], // CS pin
            .queue_size = 8,            // We want to be able to queue 7 transactions at a time
            .flags = SPI_DEVICE_TXBIT_LSBFIRST,
            // .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
        };
        ret = spi_bus_add_device(LED_HOST, &devcfg, &spi[i]);
        ESP_ERROR_CHECK(ret);
    }

    init_led_matrix();
    return ret;
}
