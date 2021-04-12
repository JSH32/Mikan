#pragma once

#include <cinttypes>

#include "interrupt.h"
#include "clock.h"

namespace Mikan {
    class TimerRegister {
    public:
        /**
         * FF04 - DIV - Divider Register (R/W)
         * This register is incremented at rate of 16384Hz (~16779Hz on SGB). Writing any value to this register resets it to 00h.
         * Note: The divider is affected by CGB double speed mode, and will increment at 32768Hz in double speed.
         */
        uint8_t div;

        /**
         * FF05 - TIMA - Timer counter (R/W)
         * This timer is incremented by a clock frequency specified by the TAC register ($FF07). 
         * When the value overflows (gets bigger than FFh) then it will be reset to the value specified in TMA (FF06),
         * and an interrupt will be requested, as described below.
         */
        uint8_t tima;

        /**
         * FF06 - TMA - Timer Modulo (R/W)
         * When the TIMA overflows, this data will be loaded.
         */
        uint8_t tma;

        /**
         * FF07 - TAC - Timer Control (R/W)
         * Bit  2   - Timer Enable
         * Bits 1-0 - Input Clock Select
         *            00: CPU Clock / 1024 (DMG, CGB:   4096 Hz, SGB:   ~4194 Hz)
         *            01: CPU Clock / 16   (DMG, CGB: 262144 Hz, SGB: ~268400 Hz)
         *            10: CPU Clock / 64   (DMG, CGB:  65536 Hz, SGB:  ~67110 Hz)
         *            11: CPU Clock / 256  (DMG, CGB:  16384 Hz, SGB:  ~16780 Hz)
         */
        uint8_t tac;
    };

    /**
     * Sometimes it's useful to have a timer that interrupts at regular intervals for routines that require periodic or
     * percise updates. The timer in the GameBoy has a selectable frequency of 4096, 16384, 65536, or 262144 Hertz.
     * This frequency increments the Timer Counter (TIMA). When it overflows, it generates an interrupt. It is then loaded
     * with the contents of Timer Modulo (TMA).
     */
    class Timer {
    public:
        Timer(Interrupt& interrupt) 
            : interrupt(interrupt) {}

        uint8_t get(uint16_t address);
        void set(uint16_t address, uint8_t value);
        void next(uint32_t cycles);
    private:
        TimerRegister registers;
        Interrupt& interrupt;
        Clock divClock = Clock(256);
        Clock tmaClock = Clock(1024);
    };
}