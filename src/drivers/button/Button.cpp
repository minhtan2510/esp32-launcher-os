#include "esp_log.h"
#include "Button.hpp"

static constexpr auto TAG = "Button";

namespace launcher::button
{
    Button::Button(ButtonId id, gpio_num_t pin)
        : id_(id),
          pin_(pin),
          stableState_(false),
          lastRawState_(false),
          lastDebounceTime_(0),
          pressStartTime_(0),
          longPressReported_(false)
    {
        gpio_config_t config = {};

        config.pin_bit_mask = (1ULL << pin_);
        config.mode = GPIO_MODE_INPUT;
        config.pull_up_en = GPIO_PULLUP_DISABLE;
        config.pull_down_en = GPIO_PULLDOWN_DISABLE;
        config.intr_type = GPIO_INTR_DISABLE;

        gpio_config(&config);

        stableState_ = !gpio_get_level(pin_);
        lastRawState_ = stableState_;
    }

    ButtonEvent Button::update(uint32_t nowMs)
    {
        ButtonEvent event
        {
            id_,
            ButtonEventType::None,
        };

        const bool rawState = !gpio_get_level(pin_);

        //* Update lasted state
        if (rawState != lastRawState_)
        {
            lastRawState_ = rawState;
            lastDebounceTime_ = nowMs;
        }

        //* Debounce handler
        if ((nowMs - lastDebounceTime_) < DEBOUNCE_MS)
        {
            return event;
        }

        //*Button short press handle
        if (rawState != stableState_)
        {
            stableState_ = rawState;
            
            if(stableState_)
            {
                pressStartTime_ = nowMs;
                longPressReported_ = false;
                event.type = ButtonEventType::Pressed;
            }
            else
            {
                event.type = ButtonEventType::Released;
            }
            return event;
        }

        //* Button long press handle
        if (rawState && !longPressReported_ && (nowMs - pressStartTime_ >= LONG_PRESS_MS))
        {
            longPressReported_ = true;
            event.type = ButtonEventType::LongPress;
            return event;
        }

        return event;
    }
    
    void printButtonEvent(const launcher::button::ButtonEvent& event)
    {
        using namespace launcher::button;

        if (event.type == ButtonEventType::None)
        {
            return;
        }

        const char* buttonName = "";

        switch (event.id)
        {
            case ButtonId::Up:
                buttonName = "UP";
                break;

            case ButtonId::Select:
                buttonName = "SELECT";
                break;

            case ButtonId::Down:
                buttonName = "DOWN";
                break;
        }

        const char* eventName = "";

        switch (event.type)
        {
            case ButtonEventType::Pressed:
                eventName = "Pressed";
                break;

            case ButtonEventType::Released:
                eventName = "Released";
                break;

            case ButtonEventType::ShortPress:
                eventName = "ShortPress";
                break;

            case ButtonEventType::LongPress:
                eventName = "LongPress";
                break;

            case ButtonEventType::DoublePress:
                eventName = "DoublePress";
                break;

            default:
                eventName = "Unknown";
                break;
        }
        ESP_LOGI(TAG, "[%s] %s", buttonName, eventName);
    }
} // namespace launcher::drivers