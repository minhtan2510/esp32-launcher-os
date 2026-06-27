#include "BootManager.hpp"

#include "config/BuildConfig.hpp"

#include "drivers/button/ButtonTask.hpp"
#include "drivers/display/Display.hpp"

#include "utils/ScopedTimer/ScopedTimer.hpp"

#include "esp_log.h"

namespace launcher::boot
{
    static constexpr auto TAG = "BootManager";

    void BootManager::init()
    {
        ESP_LOGI(TAG, "========= Booting LauncherOS =========");

#ifdef ENABLE_MEASURE_SYS_INIT_TIME
        launcher::utils::ScopedTimer BootManagerTimer("BootManager");
#endif

        launcher::button::initButtons();
        launcher::display::initDisplay();

        //TODO:
        // launcher::event::initEventQueue();
        // launcher::launcher::initLauncher();

        ESP_LOGI(TAG, "=========== Boot completed ===========");
    }

} // namespace launcher::boot