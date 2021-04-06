#pragma once

#include <cstdint>

namespace Mikan {
    /**
     * @brief FF0F - IF - Interrupt Flag (R/W)
     */
    class Interrupt {
    public:
        /**
         * Bit 0: V-Blank  Interrupt Request (INT 40h)  (1=Request)
         * Bit 1: LCD STAT Interrupt Request (INT 48h)  (1=Request)
         * Bit 2: Timer    Interrupt Request (INT 50h)  (1=Request)
         * Bit 3: Serial   Interrupt Request (INT 58h)  (1=Request)
         * Bit 4: Joypad   Interrupt Request (INT 60h)  (1=Request)
         */
        uint8_t data = 0x00;

        void set(InterruptFlag flag);
    };

    /**
     * @brief Interrupt modes in the CPU
     */
    enum InterruptFlag {
        VBlank  = 0,
        LCDStat = 1,
        Timer   = 2,
        Serial  = 3,
        Joypad  = 4,
    };
}