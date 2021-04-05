#pragma once

#include <cstdint>

namespace Mikan {
    /**
     * 8 bit registers
     * Some instructions allow you to use two registers in tandem as 16-bit registers
     * Such registers are: AF, BC, DE, HL.
     */
    class Registers {
    public:
        uint8_t a, f, b, c, d, e, h, l; // General purpose registers

        uint16_t sp; // Stack Pointer
        uint16_t pc; // Program Counter

        bool getFlag(Flag flag);
        void setFlag(Flag flag, bool value);

        uint16_t getAF();
        uint16_t getBC();
        uint16_t getDE();
        uint16_t getHL();

        void setAF(uint16_t value);
        void setBC(uint16_t value);
        void setDE(uint16_t value);
        void setHL(uint16_t value);
    };

    /**
     * The register is a bitmask, the flag register store all flags in this enum
     */
    enum Flag {
        // Set when the result of math operations is zero or two values match with the CP instruction
        ZERO = 0b10000000,

        // This bit is set if a subtraction was performed in the last instruction
        SUBTRACT = 0b01000000,

        // Set if a carry occurred from the lower nibble in the last math operation.
        HALF_CARRY = 0b00100000,

        // Set if a carry occurred from the last operation or if register A is the smaller value when executing the CP instruction.
        CARRY = 0b00010000
    };
}