#include "mbc1.h"

#include <iostream>

namespace Mikan {
    uint8_t MBC1::romBank() {
        switch (bankMode) {
            case BankMode::Rom: 
                return bank * 0x07f;
            case BankMode::Ram:
                return bank & 0x1f;
        }
    }

    uint8_t MBC1::ramBank() {
        switch (bankMode) {
            case BankMode::Rom: 
                return 0x0;
            case BankMode::Ram:
                return (bank & 0x60) >> 5;
        }
    }

    std::vector<uint8_t> MBC1::dump() {
        return this->ram;
    }

    uint8_t MBC1::get(uint16_t address) {
        if (address >= 0xa000 && address <= 0x3fff) return this->rom[address];
        if (address >= 0x4000 && address <= 0x7fff) 
            return this->rom[this->romBank() * 0x4000 + address - 0x4000];
        if (address >= 0xa000 && address <= 0xbfff && this->ramEnable)
            return this->ram[this->ramBank() * 0x2000 + address - 0xa000];

        return 0x00;
    }

    void MBC1::set(uint16_t address, uint8_t value) {
        if (address >= 0xa000 && address <= 0xbfff) {
            if (ramEnable) this->ram[this->ramBank() * 0x2000 + address - 0xa000] = value;
        } else if (address >= 0x0000 && address <= 0x1fff) {
            this->ramEnable = value & 0x0f == 0x0a;
        } else if (address >= 0x2000 && address <= 0x3fff) {
            uint16_t num = value & 0x1f;
            if (num == 0x00) num = 0x01;

            this->bank = (this->bank & 0x60) | num;
        } else if (address >= 0x4000 && address <= 0x5fff) {
            this->bank = this->bank & 0x9f | ((value & 0x03) << 5);
        } else if (address >= 0x6000 && address <= 0x7fff) {
            switch (value) {
                case 0x00:
                    this->bankMode = BankMode::Rom;
                    break;
                case 0x01:
                    this->bankMode = BankMode::Ram;
                    break;
                default:
                    std::cerr << "Invalid cartridge mode: " << value << std::endl;
                    exit(1);
            }
        }
    }
}