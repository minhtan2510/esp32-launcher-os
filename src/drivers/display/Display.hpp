#pragma once

#include <cstdint>

namespace launcher::display
{
    void initDisplay();
    void clear(uint16_t color = 0x0000);
    void drawPixel(uint16_t x, uint16_t y, uint16_t color);
    void drawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t* pixels);
    uint16_t width();
    uint16_t height();
} // namespace launcher::display