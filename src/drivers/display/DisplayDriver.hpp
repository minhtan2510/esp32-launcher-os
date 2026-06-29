#pragma once

#include <stdint.h>
#include "esp_lcd_panel_ops.h"

#include "config/BuildConfig.hpp"

namespace launcher::display
{
    enum class DisplayRotation
    {
        Deg0,
        Deg90,
        Deg180,
        Deg270
    };
    class DisplayDriver
    {
    public:
        void init();

        ~DisplayDriver();

        void clear(uint16_t color);
        void drawPixel(uint16_t x, uint16_t y, uint16_t color);
        void drawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t* pixels);
        void setRotation(DisplayRotation rotation);
        
        uint16_t width() const;
        uint16_t height() const;

    private:
        static constexpr uint16_t MaxLinePixels = LCD_H_RES > LCD_V_RES ? LCD_H_RES : LCD_V_RES;
        esp_lcd_panel_handle_t panel_ = nullptr;
        uint16_t* lineBuffer_ = nullptr;
        uint16_t width_ = LCD_H_RES;
        uint16_t height_ = LCD_V_RES;
    };

}
