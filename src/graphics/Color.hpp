#pragma once

#include <stdint.h>

namespace launcher::graphics
{
    enum class Color : uint16_t
    {
        Black   = 0x0000,
        White   = 0xFFFF,

        Red     = 0xF800,
        Green   = 0x07E0,
        Blue    = 0x001F,

        Yellow  = 0xFFE0,
        Cyan    = 0x07FF,
        Magenta = 0xF81F,

        Gray    = 0x8410,
        Orange  = 0xFD20,
    };

}