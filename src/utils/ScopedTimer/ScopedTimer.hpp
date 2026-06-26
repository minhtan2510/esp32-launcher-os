#pragma once

#include <cstdint>

namespace launcher::utils
{
    class ScopedTimer
    {
    public:
        explicit ScopedTimer(const char* name);
        ~ScopedTimer();

        uint64_t elapsedUs() const;
        double elapsedMs() const;
        double elapsedSeconds() const;

    private:
        const char* name_;
        int64_t startUs_;
    };

} // namespace launcher::utils