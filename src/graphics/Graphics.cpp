#include "graphics/Graphics.hpp"

#include "drivers/display/Display.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <cstdlib>
#include <algorithm>

namespace launcher::graphics
{
    constexpr int MAX_LCD_LINE_PIXELS = LCD_H_RES > LCD_V_RES ? LCD_H_RES : LCD_V_RES;

    uint16_t hLineBuffer[MAX_LCD_LINE_PIXELS];
    uint16_t vLineBuffer[MAX_LCD_LINE_PIXELS];
    
    void clear(Color color)
    {
        launcher::display::clear(static_cast<uint16_t>(color));
    }

    void drawPixel(int x, int y, Color color)
    {
        launcher::display::drawPixel(x, y, static_cast<uint16_t>(color));
    }

    void drawHLine(int x, int y, int length, Color color)
    {
        if (length <= 0)
            return;

        if (y < 0 || y >= launcher::display::height() || x >= launcher::display::width())
            return;

        if (x < 0)
        {
            length += x;
            x = 0;
        }

        length = std::min<int>(length, launcher::display::width() - x);
        if (length <= 0)
            return;

        const uint16_t color565 = static_cast<uint16_t>(color);
        std::fill_n(hLineBuffer, length, color565);
        launcher::display::drawBitmap(x, y, length, 1, hLineBuffer);
    }

    void drawVLine(int x, int y, int length, Color color)
    {
        if (length <= 0)
            return;

        if (x < 0 || x >= launcher::display::width() || y >= launcher::display::height())
            return;

        if (y < 0)
        {
            length += y;
            y = 0;
        }

        length = std::min<int>(length, launcher::display::height() - y);
        if (length <= 0)
            return;

        const uint16_t color565 = static_cast<uint16_t>(color);
        std::fill_n(vLineBuffer, length, color565);
        launcher::display::drawBitmap(x, y, 1, length, vLineBuffer);
    }

    void drawRect(int x, int y, int width, int height, Color color)
    {
        drawHLine(x, y, width, color);
        drawHLine(x, y + height - 1, width, color);
        drawVLine(x, y, height, color);
        drawVLine(x + width - 1, y, height, color);
    }

    void fillRect(int x, int y, int width, int height, Color color)
    {
        for (int i = 0; i < height; i++)
        {
            drawHLine(x, y + i, width, color);
        }
    }

    void drawLine(int x0, int y0, int x1, int y1, Color color)
    {
        int dx = abs(x1 - x0);
        int sx = x0 < x1 ? 1 : -1;

        int dy = -abs(y1 - y0);
        int sy = y0 < y1 ? 1 : -1;

        int err = dx + dy;

        while (true)
        {
            drawPixel(x0, y0, color);

            if (x0 == x1 && y0 == y1)
            {
                break;
            }

            int e2 = err * 2;

            if (e2 >= dy)
            {
                err += dy;
                x0 += sx;
            }

            if (e2 <= dx)
            {
                err += dx;
                y0 += sy;
            }
        }
    }

    void drawBitmap(int x, int y, const Bitmap &bitmap)
    {
        launcher::display::drawBitmap(x, y, bitmap.width, bitmap.height, bitmap.pixels);
    }
}
