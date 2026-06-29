#pragma once

#include "graphics/Color.hpp"
#include "config/BuildConfig.hpp"

namespace launcher::graphics
{
    struct Bitmap
    {
        uint16_t width;
        uint16_t height;
        const uint16_t* pixels;
    };

    void clear(Color color);
    void drawPixel(int x, int y, Color color);
    void drawHLine(int x, int y, int length, Color color);
    void drawVLine(int x, int y, int length, Color color);
    void drawLine(int x0, int y0, int x1, int y1, Color color);
    void drawRect(int x, int y, int width, int height, Color color);
    void fillRect(int x, int y, int width, int height, Color color);

    void drawBitmap(int x, int y, const Bitmap& bitmap);
}
