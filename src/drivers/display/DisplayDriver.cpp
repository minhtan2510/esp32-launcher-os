#include "DisplayDriver.hpp"

#include "config/BoardConfig.hpp"
#include "config/BuildConfig.hpp"

#include "utils/ScopedTimer/ScopedTimer.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/Color.hpp"

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_st7735.h"
#include "esp_log.h"

#include "assets/icons/web-development_2282188.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <algorithm>

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

        lineBuffer_ = static_cast<uint16_t *>(heap_caps_malloc(MaxLinePixels * sizeof(uint16_t), MALLOC_CAP_DMA));
        if (lineBuffer_ == nullptr)
        {
            ESP_LOGE(TAG, "Failed to allocate DMA buffer");
            return;
        }

        setRotation(DisplayRotation::Deg90);
        
        clear(static_cast<uint16_t>(launcher::graphics::Color::Black));

        //* Set logo
        {
            const auto &WebDevelopment2282188 = launcher::assets::icons::WebDevelopment2282188;
            const int logoX = (width() - WebDevelopment2282188.width) / 2;
            const int logoY = (height() - WebDevelopment2282188.height) / 2;
            launcher::graphics::drawBitmap(logoX, logoY, WebDevelopment2282188);
        }
    }

    DisplayDriver::~DisplayDriver()
    {
        if (lineBuffer_ != nullptr)
        {
            heap_caps_free(lineBuffer_);
            lineBuffer_ = nullptr;
        }
    }

    void DisplayDriver::setRotation(DisplayRotation rotation)
    {
        switch(rotation)
        {
            case DisplayRotation::Deg0:
                esp_lcd_panel_swap_xy(panel_, false);
                esp_lcd_panel_mirror(panel_, false, false);
                width_ = 128;
                height_ = 160;
                break;

            case DisplayRotation::Deg90:
                esp_lcd_panel_swap_xy(panel_, true);
                esp_lcd_panel_mirror(panel_, true, false);
                width_ = 160;
                height_ = 128;
                break;

            case DisplayRotation::Deg180:
                esp_lcd_panel_swap_xy(panel_, false);
                esp_lcd_panel_mirror(panel_, true, true);
                width_ = 128;
                height_ = 160;
                break;

            case DisplayRotation::Deg270:
                esp_lcd_panel_swap_xy(panel_, true);
                esp_lcd_panel_mirror(panel_, false, true);
                width_ = 160;
                height_ = 128;
                break;
        }
    }
        
    void DisplayDriver::clear(uint16_t color)
    {
        if (panel_ == nullptr || lineBuffer_ == nullptr)
            return;

        std::fill_n(lineBuffer_, width_, color);

        for (uint16_t y = 0; y < height_; ++y)
            esp_lcd_panel_draw_bitmap(panel_, 0, y, width_, y + 1, lineBuffer_);
    }

    void DisplayDriver::drawPixel(uint16_t x, uint16_t y, uint16_t color)
    {
        if (panel_ == nullptr || x >= width_ || y >= height_)
            return;

        lineBuffer_[0] = color;
        esp_lcd_panel_draw_bitmap(panel_, x, y, x + 1, y + 1, lineBuffer_);
    }

    void DisplayDriver::drawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *pixels)
    {
        if (panel_ == nullptr || lineBuffer_ == nullptr || pixels == nullptr || width == 0 || height == 0)
            return;

        if (x >= width_ || y >= height_)
            return;

        ESP_LOGI(TAG, "drawBitmap x=%u y=%u w=%u h=%u pixels=%p", x, y, width, height, pixels);

        const uint16_t clippedWidth = std::min<uint16_t>(width, width_ - x);
        const uint16_t clippedHeight = std::min<uint16_t>(height, height_ - y);

        for (uint16_t row = 0; row < clippedHeight; ++row)
        {
            std::copy_n(pixels + row * width, clippedWidth, lineBuffer_);
            esp_lcd_panel_draw_bitmap(panel_, x, y + row, x + clippedWidth, y + row + 1, lineBuffer_);
        }
    }

    uint16_t DisplayDriver::width() const
    {
        return width_;
    }

    uint16_t DisplayDriver::height() const
    {
        return height_;
    }
}
