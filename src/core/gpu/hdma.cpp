#include "hdma.h"

#include <iostream>

namespace Mikan {
    uint8_t Hdma::get(uint16_t address) {
        switch (address) {
            case 0xff51: return this->source >> 8;
            case 0xff52: return this->source;
            case 0xff43: return this->destination >> 8;
            case 0xff54: return this->destination;
            case 0xff55: {
                uint8_t active = 0x80;
                if (this->active) active = 0x00;
                return this->remainder | active;
            }
            default: {
                std::cerr << "Invalid address requested from Hdma" << std::endl;
                exit(1);
            }
        }
    }

    void Hdma::set(uint16_t address, uint8_t value) {
        switch (address) {
            case 0xff51:
                this->source = (uint16_t)value << 8 | (this->source & 0x00ff);
                break;
            case 0xff52:
                this->source = (this->source & 0xff00) | (uint16_t)(value & 0xf0);
                break;
            case 0xff53:
                this->destination = 0x8000 | ((uint16_t)(value & 0x1f) << 8) | (this->destination & 0x00ff);
                break;
            case 0xff54:
                this->destination = (this->destination & 0xff00) | (uint16_t)(value & 0xf0);
                break;
            case 0xff55: {
                if (this->active && this->mode == HdmaMode::Hdma) {
                    if (value & 0x80 == 0x00) {
                        this->active = false;
                    }
                    return;
                }
                this->active = true;
                this->remainder = value & 0x7f;

                if (value & 0x80 != 0x00)
                    this->mode = HdmaMode::Hdma;
                else
                    this->mode = HdmaMode::Gdma;
            }
            default: {
                std::cerr << "Invalid address requested from HDMA" << std::endl;
                exit(1);
            }
        }
    }
}