//* buttons.hpp
#pragma once

#include <cstdint>
#include <driver/gpio.h>

namespace launcher::button
{
    enum class ButtonId : uint8_t
    {
        Up,
        Select,
        Down,
    };

    enum class ButtonEventType : uint8_t
    {
        None,
        Pressed,
        Released,
        ShortPress,
        LongPress,
        DoublePress,
    };

    struct ButtonEvent
    {
        ButtonId id;
        ButtonEventType type;
    };

    //*=================================================================================================

    class Button
    {
    public:
        static constexpr uint32_t DEBOUNCE_MS = 30; // Debounce time in ms
        static constexpr uint32_t LONG_PRESS_MS = 1000;

        Button(ButtonId id, gpio_num_t pin);
        ButtonEvent update(uint32_t now_ms);
        void printButtonEvent(const launcher::button::ButtonEvent& event);

    private:
        ButtonId id_;
        gpio_num_t pin_;

        bool stableState_;
        bool lastRawState_;

        uint32_t lastDebounceTime_;
        uint32_t pressStartTime_;

        bool longPressReported_;
    };

    void printButtonEvent(const launcher::button::ButtonEvent& event);
    
}; // namespace launcher::button
