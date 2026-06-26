#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "drivers/button/ButtonTask.hpp"
#include "utils/ScopedTimer/ScopedTimer.hpp"
#include "core/boot/BootManager.hpp"

using namespace launcher::button;

extern "C" void app_main()
{
    //* Initialization logic block
    {
        launcher::boot::BootManager::init();
    }

    while (true)
    {
        vTaskDelay(portMAX_DELAY);
    }
}