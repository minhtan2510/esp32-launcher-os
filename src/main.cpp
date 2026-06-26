#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "drivers/button/ButtonTask.hpp"

using namespace launcher::button;

extern "C" void app_main()
{
    launcher::button::initButtons();
    // launcher::display::initDisplay();
    // launcher::event::initEventQueue();
    // launcher::launcher::initLauncher();

    while (true)
    {
        vTaskDelay(portMAX_DELAY);
    }
}