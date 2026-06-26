#include "ButtonTask.hpp"

#include "Button.hpp"
#include "config/BoardConfig.hpp"
#include "config/BuildConfig.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

using launcher::config::Pins;

namespace launcher::button
{
    static void buttonTask(void *arg)
    {
        Button btnUp(ButtonId::Up, Pins::BUTTON_UP);
        Button btnSelect(ButtonId::Select, Pins::BUTTON_SELECT);
        Button btnDown(ButtonId::Down, Pins::BUTTON_DOWN);

        while (true)
        {
            uint32_t nowMs = xTaskGetTickCount() * portTICK_PERIOD_MS;

            ButtonEvent upEvent = btnUp.update(nowMs);
            ButtonEvent selectEvent = btnSelect.update(nowMs);
            ButtonEvent downEvent = btnDown.update(nowMs);

    #ifdef ENABLE_BUTTON_LOG
            printButtonEvent(upEvent);
            printButtonEvent(selectEvent);
            printButtonEvent(downEvent);
    #endif

            // TODO:
            // eventQueue.push(upEvent);
            // eventQueue.push(selectEvent);
            // eventQueue.push(downEvent);

            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }

    void initButtons()
    {
        xTaskCreate(buttonTask, "ButtonTask", 2048, nullptr, 5, nullptr);
    }

} // namespace launcher::button