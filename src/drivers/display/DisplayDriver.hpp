#pragma once

#include <stdint.h>
#include "esp_lcd_panel_ops.h"

namespace launcher::display
{

    class DisplayDriver
    {
    public:
        void init();

        void clear(uint16_t color);

        uint16_t width() const;

        uint16_t height() const;

    private:
        esp_lcd_panel_handle_t panel_ = nullptr;

        uint16_t width_ = 128;
        uint16_t height_ = 160;
    };

}