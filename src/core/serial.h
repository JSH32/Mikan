#pragma once

#include <cinttypes>

#include "interrupt.h"
#include "memory.h"

namespace Mikan {
    /**
     * Communication between two Gameboys happens one byte at a time. One Gameboy acts as the master, uses its internal
     * clock, and thus controls when the exchange happens. The other one uses an external clock (i.e., the one inside the
     * other Gameboy) and has no control over when the transfer happens. If it hasn't gotten around to loading up the next
     * data byte at the time the transfer begins, the last one will go out again. Alternately, if it's ready to send the
     * next byte but the last one hasn't gone out yet, it has no choice but to wait.
     * 
     * TODO: Support link cable of two emulators over TCP
     */
    class Serial : public Memory {
    public:
        Serial(Interrupt& interruptFlag) 
            : interruptFlag(interruptFlag) {}

        // Memory implementation
        uint8_t get(uint16_t address);
        void set(uint16_t address, uint8_t value);
    private:
        Interrupt& interruptFlag;

        uint8_t data = 0x00;
        uint8_t control = 0x00;
    };
}