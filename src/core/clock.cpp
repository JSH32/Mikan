#include "clock.h"

namespace Mikan {
    uint32_t Clock::next(uint32_t cycles) {
        this->num += cycles;
        uint32_t ret = this->num / this->interval;
        this->num = this->num % this->interval;
        return ret;
    }
}