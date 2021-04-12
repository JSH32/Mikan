#pragma once

#include <cstdint>

namespace Mikan {
    class Memory {
    public:
        virtual uint8_t get(uint16_t address) = 0;
        virtual void set(uint16_t address, uint8_t value) = 0;

        uint16_t getWord(uint16_t address);

        void setWord(uint16_t address, uint16_t value);
    };
}