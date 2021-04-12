#pragma once

#include "../memory.h"
#include "cartridge.h"


namespace Mikan {
    /**
     * Small games of not more than 32KBytes ROM do not require a MBC chip for ROM banking. 
     * The ROM is directly mapped to memory at 0000-7FFFh. Optionally up to 8KByte of RAM could be connected at A000-BFFF, 
     * even though that could require a tiny MBC-like circuit, but no real MBC chip.
     */
    class RomOnly : public Memory, public Cartridge {
    public:
        RomOnly(std::vector<uint8_t> rom) : rom(rom) {};

        // Memory implementation
        uint8_t get(uint16_t address);
        void set(uint16_t address, uint8_t value);

        // Cartridge implementation
        std::vector<uint8_t> dump();
    private:
        std::vector<uint8_t> rom;
    };
}