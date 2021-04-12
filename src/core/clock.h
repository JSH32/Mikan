#pragma once

#include <cinttypes>

namespace Mikan {
    class Clock {
    public:
        Clock(uint32_t interval) 
            : interval(interval) {}

        uint32_t next(uint32_t cycles);

        uint32_t interval;
        uint32_t num;
    };
}