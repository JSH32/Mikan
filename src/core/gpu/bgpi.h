#pragma once

#include <cinttypes>

namespace Mikan {
    /**
     * This register is used to address a byte in the CGBs Background Palette Memory. Each two byte in that memory define a
     * color value. The first 8 bytes define Color 0-3 of Palette 0 (BGP0), and so on for BGP1-7.
     *  Bit 0-5   Index (00-3F)
     *  Bit 7     Auto Increment  (0=Disabled, 1=Increment after Writing)
     * Data can be read/written to/from the specified index address through Register FF69. When the Auto Increment bit is
     * set then the index is automatically incremented after each <write> to FF69. Auto Increment has no effect when
     * <reading> from FF69, so the index must be manually incremented in that case. Writing to FF69 during rendering still
     * causes auto-increment to occur.
     * Unlike the following, this register can be accessed outside V-Blank and H-Blank.
     */
    class Bgpi {
        uint8_t index = 0x00;
        bool autoIncrement = false;

        uint8_t get();
        uint8_t set(uint8_t value);
    };
}