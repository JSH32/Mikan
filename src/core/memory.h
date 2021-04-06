#pragma once

#include <cstdint>

namespace Mikan {
    class Memory {
        virtual uint8_t get(uint16_t address) = 0;
        virtual void set(uint16_t address, uint8_t value) = 0;

        uint16_t get_word(uint16_t address) {
            return (uint16_t)this->get(address) | ((uint16_t)(this->get(address+1)) << 8);
        }

        void set_word(uint16_t address, uint16_t value) {
            this->set(address, value & 0xFF);
            this->set(address + 1, value >> 8);
        }
    };
}