#pragma once

#include <cstdint>

#include "interrupt.h"

namespace Mikan {
    /**
     * MMU (Memory Management Unit) stores all references to non in-operation memory, all memory except the registers will pass through this unit
     */
    class MMU {
    public:
        /**
         * High page memory, accessed between ranges 0xff80-0xfffe and located on the CPU die. 
         * During a DMA transfer you may not access external memory
         * You must access memory from the HRAM
         */
    private:
        uint8_t hram[0x7f];

        Interrupt interrupt;
    };
}