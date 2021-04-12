#pragma once

#include "romonly.h"

namespace Mikan {
    uint8_t RomOnly::get(uint16_t address) {
        return this->rom[address];
    }

    // No RAM so cannot set MBC ram
    void RomOnly::set(uint16_t address, uint8_t value) {}

    // No RAM so cannot dump MBC ram
    std::vector<uint8_t> RomOnly::dump() {
        return std::vector<uint8_t>();
    }
}