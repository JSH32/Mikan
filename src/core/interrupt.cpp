#include "interrupt.h"

namespace Mikan {
    void Interrupt::set(InterruptFlag flag) {
        this->data |= 1 << (uint8_t)flag;
    }
}