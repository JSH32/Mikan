#pragma once

#include <cinttypes>

namespace Mikan {
    /**
     * LCD Status Register
     */
    class Stat {
    public:
        // Bit 6 - LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
        bool lyInterrupt = false;

        // Bit 5 - Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
        bool m2Interrupt = false;

        // Bit 4 - Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
        bool m1Interrupt = false;

        // Bit 3 - Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
        bool m0Interrupt = false;

        /**
         * Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Read Only)
         *    0: During H-Blank
         *    1: During V-Blank
         *    2: During Searching OAM
         *    3: During Transferring Data to LCD Driver
         */
        uint8_t mode = 0x00;
    };
}