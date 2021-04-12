#include "serial.h"

#include <iostream>

namespace Mikan {
    uint8_t Serial::get(uint16_t address) {
        switch (address) {
            case 0xff01: return this->data;
            case 0xff02: return this->control;
            default: {
                std::cerr << "Serial may only be accessed over addresses 0xff01, 0xff02" << std::endl;
                exit(1);
            }
        }
    }

    void Serial::set(uint16_t address, uint8_t value) {
        switch (address) {
            case 0xff01: {
                this->data = value;
                return;
            }
            case 0xff02: {
                this->control = value;
                return;
            }
            default: {
                std::cerr << "Serial may only be accessed over addresses 0xff01, 0xff02" << std::endl;
                exit(1);
            }
        }
    }
}