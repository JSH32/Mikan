#include "mmu.h"

namespace Mikan {
    uint8_t MMU::get(uint16_t address) {

    }

    void MMU::set(uint16_t address, uint8_t value) {

    }

    void MMU::switchSpeed() {
        if (shift) {
            if (speed == Speed::Double) {
                speed = Speed::Normal;
            } else {
                speed = Speed::Double;
            }
        }
        shift = false;
    }
}