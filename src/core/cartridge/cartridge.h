#pragma once

#include "../memory.h"

#include <string>
#include <vector>

namespace Mikan {
    class Cartridge: public virtual Memory {
    public:
        /**
         * Get the title of the game in uppercase ASCII
         * If it is less than 16 characters then the remaining bytes are filled with 00's
         */
        std::string title();

        /**
         * Get all cartridge RAM content
         */
        virtual std::vector<uint8_t> dump() = 0;
    };
}