#pragma once

#include "interrupt.h";

namespace Mikan {
    /**
     * FF00 - P1/JOYP - Joypad (R/W)
     * 
     * Bit 7 - Not used
     * Bit 6 - Not used
     * Bit 5 - P15 Select Button Keys      (0=Select)
     * Bit 4 - P14 Select Direction Keys   (0=Select)
     * Bit 3 - P13 Input Down  or Start    (0=Pressed) (Read Only)
     * Bit 2 - P12 Input Up    or Select   (0=Pressed) (Read Only)
     * Bit 1 - P11 Input Left  or Button B (0=Pressed) (Read Only)
     * Bit 0 - P10 Input Right or Button A (0=Pressed) (Read Only)
     */
    class Joypad {
    public:
        Interrupt& interrupt;

        uint8_t matrix = 0xff;
        uint8_t select = 0x00;

        Joypad(Interrupt& interrupt) : interrupt(interrupt) {};

        void keyDown(JoypadKey key);
        void keyUp(JoypadKey key);
    };

    enum JoypadKey {
        Right  = 0b00000001,
        Left   = 0b00000010,
        Up     = 0b00000100,
        Down   = 0b00001000,
        A      = 0b00010000,
        B      = 0b00100000,
        Select = 0b01000000,
        Start  = 0b10000000
    };
}