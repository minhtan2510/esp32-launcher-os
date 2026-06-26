#include "ScopedTimer.hpp"

#include "esp_log.h"
#include "esp_timer.h"

namespace launcher::utils
{
    static constexpr auto TAG = "ScopedTimer";

    ScopedTimer::ScopedTimer(const char *name)
        : name_(name),
          startUs_(esp_timer_get_time())
    {}

    ScopedTimer::~ScopedTimer()
    {
        const auto us = elapsedUs();

        ESP_LOGI(TAG, "%s completed in %.3f ms (%.6f s)", name_, us / 1000.0, us / 1000000.0);
    }

    uint64_t ScopedTimer::elapsedUs() const
    {
        return esp_timer_get_time() - startUs_;
    }

    double ScopedTimer::elapsedMs() const
    {
        return elapsedUs() / 1000.0;
    }

    double ScopedTimer::elapsedSeconds() const
    {
        return elapsedUs() / 1000000.0;
    }
} // namespace launcher::utils