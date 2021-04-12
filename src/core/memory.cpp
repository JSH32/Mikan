#include "memory.h"

namespace Mikan {
    uint16_t Memory::getWord(uint16_t address) {
        return (uint16_t)this->get(address) | ((uint16_t)(this->get(address+1)) << 8);
    }

    void Memory::setWord(uint16_t address, uint16_t value) {
        this->set(address, value & 0xFF);
        this->set(address + 1, value >> 8);
    }
}