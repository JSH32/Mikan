#pragma once

#include <cstdint>

#include "memory.h"
#include "interrupt.h"
#include "joypad.h"
#include "cartridge/cartridge.h"
#include "gpu/hdma.h"
#include "timer.h"
#include "serial.h"

namespace Mikan {
    /**
     * @brief Speed mode address located at 0xff4d
     */
    enum class Speed {
        Normal = 0x01,
        Double = 0x02
    };

    /**
     * MMU (Memory Management Unit) stores all references to non in-operation memory, all memory except the registers will pass through this unit
     */
    class MMU : public Memory {
    public:
        MMU(Cartridge& cartridge);

        Cartridge& cartridge;
        Speed speed = Speed::Normal;
        bool shift = false;
        Joypad joypad = Joypad(interruptFlag);
        Timer timer = Timer(interruptFlag);
        Serial serial = Serial(interruptFlag);

        /**
         * Switch the speed to the opposite option
         */
        void switchSpeed();

        // Memory implementation
        uint8_t get(uint16_t address);
        void set(uint16_t address, uint8_t value);
    private:
        /**
         * High page memory, accessed between ranges 0xff80-0xfffe and located on the CPU die. 
         * During a DMA transfer you may not access external memory
         * You must access memory from the HRAM
         */
        uint8_t hram[0x7f];

        /**
         * Internal workram 
         */
        uint8_t wram[0x8000];
        uint8_t wramBank = 0x01;

        Hdma hdma;

        Interrupt interruptFlag;
        uint8_t interruptEnable = 0x00;
    };
}