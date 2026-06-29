#include "core/boot/BootManager.hpp"

#include "utils/ScopedTimer/ScopedTimer.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

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
