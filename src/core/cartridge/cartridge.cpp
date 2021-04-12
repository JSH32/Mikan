#include "cartridge.h"

#include "romonly.h"
#include "mbc1.h"

#include <iostream>

namespace Mikan {
    std::string Cartridge::title() {
        std::string str;
        
        uint16_t start = 0x0134;
        uint16_t end;
        if (this->get(0x0143) == 0x80)
            end = 0x013e;
        else
            end = 0x0143;

        for (uint16_t i = start; i < end; i++) {
            uint8_t value = this->get(i);

            if (value == 0) break;
            str.append(std::string((char*)value));
        }

        return str;
    }

    Cartridge& Cartridge::init(std::vector<uint8_t> rom) {
        if (rom.size() < 0x150) {
            std::cerr << "Metadata at 0100-014F is invalid." << std::endl;
            exit(1);
        }

        uint8_t maxRomSize = getRomSize(rom[0x0148]);
        if (rom.size() > maxRomSize) {
            std::cerr << "Rom size larger than maximum size: " << maxRomSize << std::endl;
            exit(1);
        }

        switch (rom[0x0147]) {
            case 0x00: return RomOnly(rom);
            case 0x01: return MBC1(rom, std::vector<uint8_t>());
            default: {
                std::cerr << "Unsupported cartridge type " << std::hex << rom[0x0147] << std::endl;
                exit(1);
            }
        }
    }
}

static uint8_t getRomSize(uint8_t value) {
    uint8_t bank = 16384;
    switch (value) {
        case 0x00: return bank * 2;
        case 0x01: return bank * 4;
        case 0x02: return bank * 8;
        case 0x03: return bank * 16;
        case 0x04: return bank * 32;
        case 0x05: return bank * 64;
        case 0x06: return bank * 128;
        case 0x07: return bank * 256;
        case 0x08: return bank * 512;
        case 0x52: return bank * 72;
        case 0x53: return bank * 80;
        case 0x54: return bank * 96;
        default: {
            std::cerr << "Invalid rom size: " << std::hex << value << std::endl;
            exit(1);
        }
    }
}