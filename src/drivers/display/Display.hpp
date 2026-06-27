#pragma once

#include <cstdint>

namespace launcher::display
{

    void initDisplay();

    void clearDisplay(uint16_t color = 0x0000);

    uint16_t width();

    uint16_t height();

} // namespace launcher::display