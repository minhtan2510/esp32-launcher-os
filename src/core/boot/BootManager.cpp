#include "BootManager.hpp"

#include "drivers/button/ButtonTask.hpp"
#include "config/BuildConfig.hpp"
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

        //TODO:
        // launcher::display::initDisplay();
        // launcher::event::initEventQueue();
        // launcher::launcher::initLauncher();

        ESP_LOGI(TAG, "=========== Boot completed ===========");
    }

} // namespace launcher::boot