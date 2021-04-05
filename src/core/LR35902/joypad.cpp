#include "joypad.h"

namespace Mikan {
    void Joypad::keyDown(JoypadKey key) {
        this->matrix &= !(uint8_t)key;
        this->interrupt.raise(InterruptFlag::Joypad);
    }

    void Joypad::keyUp(JoypadKey key) {
        this->matrix |= (uint8_t)key;
    }
}