#include "timer.h"

#include <iostream>

namespace Mikan {
    uint8_t Timer::get(uint16_t address) {
        switch (address) {
            case 0xff04: return this->registers.div;
            case 0xff05: return this->registers.tima;
            case 0xff06: return this->registers.tma;
            case 0xff07: return this->registers.tac;
            default: {
                std::cerr << "Invalid address: " << std::hex << address << std::endl;
                exit(1);
            }
        }
    }

    void Timer::set(uint16_t address, uint8_t value) {
        if (address == 0xff04) {
            this->registers.div = 0x00;
            this->divClock.num = 0x00;
        } else if (address == 0xff05) {
            this->registers.tima = value;
        } else if (address == 0xff06) {
            this->registers.tma = value;
        } else if (address == 0xff07) {
            if ((this->registers.tac & 0x03) != (value & 0x03)) {
                this->tmaClock.num = 0x00;
                switch (value & 0x03) {
                    case 0x00: {
                        this->tmaClock.interval = 1024;
                        break;
                    }
                    case 0x01: {
                        this->tmaClock.interval = 16;
                        break;
                    }
                    case 0x02: {
                        this->tmaClock.interval = 64;
                        break;
                    }
                    case 0x03: {
                        this->tmaClock.interval = 256;
                        break;
                    }
                    default: {
                        std::cerr << "Invalid clock interval" << std::endl;
                        exit(1);
                    }
                }
                this->registers.tima = this->registers.tma;
            }
            this->registers.tac = value;
        } else {
            std::cerr << "Invalid address: " << std::hex << address << std::endl;
            exit(1);
        }
    }

    void Timer::next(uint32_t cycles) {
        this->registers.div += (uint8_t)this->divClock.next(cycles);

        if ((this->registers.tac & 0x04) != 0x00) {
            uint32_t next = this->tmaClock.next(cycles);
            for (int i = 0; i < next; i++) {
                this->registers.tima += 1;
                if (this->registers.tima == 0x00) {
                    this->registers.tima = this->registers.tma;
                    this->interrupt.set(InterruptFlag::Timer);
                }
            }
        }
    }
}