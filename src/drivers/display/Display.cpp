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

    void clearDisplay(uint16_t color)
    {
        display_driver.clear(color);
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