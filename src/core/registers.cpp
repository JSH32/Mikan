#include "registers.h"

namespace Mikan {
    bool Registers::getFlag(Flag flag) {
        return this->f |= (uint8_t)flag;
    }

    void Registers::setFlag(Flag flag, bool value) {
        if (value) {
            this->f |= (uint8_t)flag;
        } else {
            this->f &= !(uint8_t)flag;
        }
    }

    uint16_t Registers::getAF() {
        return (uint16_t)(this->a << 8) | (uint16_t)this->f;
    }

    uint16_t Registers::getBC() {
        return (uint16_t)(this->b << 8) | (uint16_t)this->c;
    }

    uint16_t Registers::getDE() {
        return (uint16_t)(this->d << 8) | (uint16_t)this->e;
    }

    uint16_t Registers::getHL() {
        return (uint16_t)(this->h << 8) | (uint16_t)this->l;
    }

    void Registers::setAF(uint16_t value) {
        this->a = (uint8_t)(value >> 8);
        this->f = (uint8_t)(value & 255);
    }

    void Registers::setBC(uint16_t value) {
        this->b = (uint8_t)(value >> 8);
        this->c = (uint8_t)(value & 255);
    }

    void Registers::setDE(uint16_t value) {
        this->d = (uint8_t)(value >> 8);
        this->e = (uint8_t)(value & 255);
    }

    void Registers::setHL(uint16_t value) {
        this->h = (uint8_t)(value >> 8);
        this->l = (uint8_t)(value & 255);
    }
}