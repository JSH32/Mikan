#include "joypad.h"

#include <iostream>

namespace Mikan {
    void Joypad::keyDown(JoypadKey key) {
        this->matrix &= !(uint8_t)key;
        this->interruptFlag.set(InterruptFlag::Joypad);
    }

    void Joypad::keyUp(JoypadKey key) {
        this->matrix |= (uint8_t)key;
    }

    uint8_t Joypad::get(uint16_t address) {
        if (address != 0xff00) {
            std::cerr << "Cannot get joypad at address: " << std::hex << address << std::endl;
            exit(1);
        }

        if ((this->select & 0b00010000) == 0x00)
            return this->select | this->matrix & 0x0f;
        if ((this->select & 0b00100000) == 0x00)
            return this->select | this->matrix >> 4;

        return this->select;
    }

    void Joypad::set(uint16_t address, uint8_t value) {
        if (address != 0xff00) {
            std::cerr << "Cannot set joypad at address: " << std::hex << address << std::endl;
            exit(1);
        }

        this->select = value;
    }
}