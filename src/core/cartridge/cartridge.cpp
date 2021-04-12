#include "cartridge.h"

namespace Mikan {
    std::string Cartridge::title() {
        std::string str;
        
        uint16_t start = 0x0134;
        uint16_t end;
        if (this->get(0x0143) == 0x80)
            end = 0x013e;
        else
            end = 0x0143;

        for (uint16_t i = start; i < end; i++) {
            uint8_t value = this->get(i);

            if (value == 0) break;
            str.append(std::string((char*)value));
        }

        return str;
    }

    Cartridge& Cartridge::init(std::vector<uint8_t> rom) {

    }
}