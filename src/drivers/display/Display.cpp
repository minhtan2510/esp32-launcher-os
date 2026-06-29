#include "Display.hpp"
#include "DisplayDriver.hpp"

namespace
{
    launcher::display::DisplayDriver display_driver;
}

namespace launcher::display
{
    void initDisplay()
    {
        return display_driver.init();
    }

    void clear(uint16_t color)
    {
        display_driver.clear(color);
    }

    void drawPixel(uint16_t x, uint16_t y, uint16_t color)
    {
        return display_driver.drawPixel(x, y, color);
    }

    void drawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t* pixels)
    {
        return display_driver.drawBitmap(x, y, width, height, pixels);
    }

    uint16_t width()
    {
        return display_driver.width();
    }

    uint16_t height()
    {
        return display_driver.height();
    }

} // namespace launcher::display