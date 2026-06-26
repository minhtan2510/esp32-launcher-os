#include "ButtonTask.hpp"

#include "Button.hpp"
#include "config/BoardConfig.hpp"
#include "config/BuildConfig.hpp"

#include "utils/ScopedTimer/ScopedTimer.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

using launcher::config::Pins;

namespace launcher::button
{
    static constexpr auto TAG = "ButtonTask";

    static void buttonTask(void *arg)
    {
        Button btnUp(ButtonId::Up, Pins::BUTTON_UP);
        Button btnSelect(ButtonId::Select, Pins::BUTTON_SELECT);
        Button btnDown(ButtonId::Down, Pins::BUTTON_DOWN);

        while (true)
        {
            uint32_t nowMs = xTaskGetTickCount() * portTICK_PERIOD_MS;

#ifdef ENABLE_BUTTON_LOG
            printButtonEvent(btnUp.update(nowMs));
            printButtonEvent(btnSelect.update(nowMs));
            printButtonEvent(btnDown.update(nowMs));
#else
            btnUp.update(nowMs);
            btnSelect.update(nowMs);
            btnDown.update(nowMs);
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
#ifdef ENABLE_MEASURE_MODULE_INIT_TIME
        launcher::utils::ScopedTimer InitButtonsTimer("initButtons");
#endif
        BaseType_t res = xTaskCreate(buttonTask, "ButtonTask", 2048, nullptr, 5, nullptr);
        if(res != pdTRUE)
        {
            ESP_LOGE(TAG, "Fail to create buttonTask");
            abort();
        }
    }

} // namespace launcher::button