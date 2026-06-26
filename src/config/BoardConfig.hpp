#pragma once

#include <driver/gpio.h>
#include "sdkconfig.h"

namespace launcher::config
{
#ifdef CONFIG_IDF_TARGET_ESP32
    //* ESP32

    struct Pins
    {
        //* Buttons
        static constexpr gpio_num_t BUTTON_UP =
            GPIO_NUM_32;

        static constexpr gpio_num_t BUTTON_SELECT =
            GPIO_NUM_35;

        static constexpr gpio_num_t BUTTON_DOWN =
            GPIO_NUM_34;

        //* Display SPI
        static constexpr gpio_num_t TFT_MOSI =
            GPIO_NUM_23;

        static constexpr gpio_num_t TFT_SCLK =
            GPIO_NUM_18;

        static constexpr gpio_num_t TFT_CS =
            GPIO_NUM_5;

        static constexpr gpio_num_t TFT_DC =
            GPIO_NUM_2;

        static constexpr gpio_num_t TFT_RST =
            GPIO_NUM_4;

        static constexpr gpio_num_t TFT_BL =
            GPIO_NUM_15;
    };

#elif CONFIG_IDF_TARGET_ESP32S3
    //* ESP32-S3

    static constexpr gpio_num_t BUTTON_UP =
        GPIO_NUM_4;

    static constexpr gpio_num_t BUTTON_SELECT =
        GPIO_NUM_5;

    static constexpr gpio_num_t BUTTON_DOWN =
        GPIO_NUM_6;

    static constexpr gpio_num_t TFT_MOSI =
        GPIO_NUM_11;

    static constexpr gpio_num_t TFT_SCLK =
        GPIO_NUM_12;

    static constexpr gpio_num_t TFT_CS =
        GPIO_NUM_10;

    static constexpr gpio_num_t TFT_DC =
        GPIO_NUM_9;

    static constexpr gpio_num_t TFT_RST =
        GPIO_NUM_8;

#else

#error "Unsupported target"

#endif

} // namespace launcher::config