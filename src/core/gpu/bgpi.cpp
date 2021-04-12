#pragma once

#include "bgpi.h"

namespace Mikan {
    uint8_t Bgpi::get() {
        uint8_t temp = 0x00;
        if (this->autoIncrement) temp = 0x80;
        return autoIncrement | this->index;
    }

    uint8_t Bgpi::set(uint8_t value) {
        this->autoIncrement = value & 0x80 != 0x00;
        this->index = value & 0x3f;
    }
}