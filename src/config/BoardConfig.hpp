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
            static constexpr gpio_num_t LCD_MOSI =
                GPIO_NUM_12;

            static constexpr gpio_num_t LCD_SCLK =
                GPIO_NUM_13;

            static constexpr gpio_num_t LCD_RST =
                GPIO_NUM_14;

            static constexpr gpio_num_t LCD_CS =
                GPIO_NUM_26;

            static constexpr gpio_num_t LCD_DC =
                GPIO_NUM_27;
        };

    #elif CONFIG_IDF_TARGET_ESP32S3
        //* ESP32-S3

        static constexpr gpio_num_t BUTTON_UP =
            GPIO_NUM_4;

        static constexpr gpio_num_t BUTTON_SELECT =
            GPIO_NUM_5;

        static constexpr gpio_num_t BUTTON_DOWN =
            GPIO_NUM_6;

        static constexpr gpio_num_t LCD_MOSI =
            GPIO_NUM_11;

        static constexpr gpio_num_t LCD_SCLK =
            GPIO_NUM_12;

        static constexpr gpio_num_t LCD_CS =
            GPIO_NUM_10;

        static constexpr gpio_num_t LCD_DC =
            GPIO_NUM_9;

        static constexpr gpio_num_t LCD_RST =
            GPIO_NUM_8;

    #else

    #error "Unsupported target"

    #endif

} // namespace launcher::config