#include "DisplayDriver.hpp"

#include "config/BoardConfig.hpp"
#include "config/BuildConfig.hpp"

#include "utils/ScopedTimer/ScopedTimer.hpp"

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_st7735.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static constexpr char TAG[] = "DisplayDriver";

namespace launcher::display
{
    void DisplayDriver::init()
    {
#ifdef ENABLE_MEASURE_MODULE_INIT_TIME
        launcher::utils::ScopedTimer InitDisplayTimer("initDisplay");
#endif
        //* Config SPI
        spi_bus_config_t buscfg = {};

        buscfg.sclk_io_num = launcher::config::Pins::LCD_SCLK;
        buscfg.mosi_io_num = launcher::config::Pins::LCD_MOSI;
        buscfg.miso_io_num = -1;
        buscfg.quadwp_io_num = -1;
        buscfg.quadhd_io_num = -1;
        buscfg.max_transfer_sz = width_ * height_ * sizeof(uint16_t);

        ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

        //* Config IO
        esp_lcd_panel_io_handle_t io;

        esp_lcd_panel_io_spi_config_t io_config = {};
        io_config.cs_gpio_num = launcher::config::Pins::LCD_CS;
        io_config.dc_gpio_num = launcher::config::Pins::LCD_DC;
        io_config.spi_mode = 0;
        io_config.pclk_hz = 40 * 1000 * 1000;
        io_config.trans_queue_depth = 10;
        io_config.lcd_cmd_bits = 8;
        io_config.lcd_param_bits = 8;

        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(SPI2_HOST, &io_config, &io));

        //* Config Panel
        esp_lcd_panel_dev_config_t panel_config = {};

        panel_config.reset_gpio_num = launcher::config::Pins::LCD_RST;
        panel_config.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB;
        panel_config.bits_per_pixel = 16;

        ESP_ERROR_CHECK(esp_lcd_new_panel_st7735(io, &panel_config, &panel_));

        //* Init Panel
        ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_));
        ESP_ERROR_CHECK(esp_lcd_panel_init(panel_));
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_, true));
    }
}