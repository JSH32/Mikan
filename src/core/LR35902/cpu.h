#pragma once

#include <cstdint>

#include "registers.h"

namespace Mikan {
    /**
     * @brief LR35902 CPU
     */
    class CPU {
    public:
        Registers registers; // All the CPU registers
    };
}