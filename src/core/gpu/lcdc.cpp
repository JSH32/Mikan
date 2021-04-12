#pragma once

#include "lcdc.h"

namespace Mikan {
    bool Lcdc::bit7() { return this->data & 0b10000000 != 0x00; }
    bool Lcdc::bit6() { return this->data & 0b01000000 != 0x00; }
    bool Lcdc::bit5() { return this->data & 0b00100000 != 0x00; }
    bool Lcdc::bit4() { return this->data & 0b00010000 != 0x00; }
    bool Lcdc::bit3() { return this->data & 0b00001000 != 0x00; }
    bool Lcdc::bit2() { return this->data & 0b00000100 != 0x00; }
    bool Lcdc::bit1() { return this->data & 0b00000010 != 0x00; }
    bool Lcdc::bit0() { return this->data & 0b00000001 != 0x00; }
}