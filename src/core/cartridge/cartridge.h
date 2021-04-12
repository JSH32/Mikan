#pragma once

#include "../memory.h"

#include <string>
#include <vector>

namespace Mikan {
    class Cartridge: public virtual Memory {
    public:
        /**
         * Get the title of the game in uppercase ASCII
         * If it is less than 16 characters then the remaining bytes are filled with 00's
         */
        std::string title();

        /**
         * Get all cartridge RAM content
         */
        virtual std::vector<uint8_t> dump() = 0;

        /**
         * Specifies which Memory Bank Controller (if any) is used in the cartridge, and if further external hardware exists in
         * the cartridge.
         *  00h  ROM ONLY                 19h  MBC5
         *  01h  MBC1                     1Ah  MBC5+RAM
         *  02h  MBC1+RAM                 1Bh  MBC5+RAM+BATTERY
         *  03h  MBC1+RAM+BATTERY         1Ch  MBC5+RUMBLE
         *  05h  MBC2                     1Dh  MBC5+RUMBLE+RAM
         *  06h  MBC2+BATTERY             1Eh  MBC5+RUMBLE+RAM+BATTERY
         *  08h  ROM+RAM                  20h  MBC6
         *  09h  ROM+RAM+BATTERY          22h  MBC7+SENSOR+RUMBLE+RAM+BATTERY
         *  0Bh  MMM01
         *  0Ch  MMM01+RAM
         *  0Dh  MMM01+RAM+BATTERY
         *  0Fh  MBC3+TIMER+BATTERY
         *  10h  MBC3+TIMER+RAM+BATTERY   FCh  POCKET CAMERA
         *  11h  MBC3                     FDh  BANDAI TAMA5
         *  12h  MBC3+RAM                 FEh  HuC3
         *  13h  MBC3+RAM+BATTERY         FFh  HuC1+RAM+BATTERY
         */
        static Cartridge& init(std::vector<uint8_t> rom);
    };
}