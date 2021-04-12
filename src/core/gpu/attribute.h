#pragma once

#include <cinttypes>

namespace Mikan {
    /**
     * Bit7   OBJ-to-BG Priority (0=OBJ Above BG, 1=OBJ Behind BG color 1-3)
     *     (Used for both BG and Window. BG color 0 is always behind OBJ)
     * Bit6   Y flip          (0=Normal, 1=Vertically mirrored)
     * Bit5   X flip          (0=Normal, 1=Horizontally mirrored)
     * Bit4   Palette number  **Non CGB Mode Only** (0=OBP0, 1=OBP1)
     * Bit3   Tile VRAM-Bank  **CGB Mode Only**     (0=Bank 0, 1=Bank 1)
     * Bit2-0 Palette number  **CGB Mode Only**     (OBP0-7)
     * 
     */
    class Attribute {
    public:
        Attribute::Attribute(uint8_t value) : 
            priority(value & (1 << 7) != 0),
            yflip(value & (1 << 6) != 0),
            xflip(value & (1 << 5) != 0),
            palleteNumber0(value & (1 << 4)),
            palleteNumber1(value & 0x07),
            bank(value & (1 << 3) != 0)
        {};

        bool priority;
        bool yflip;
        bool xflip;
        uint8_t palleteNumber0;
        uint8_t palleteNumber1;
        uint8_t bank;
    };
}