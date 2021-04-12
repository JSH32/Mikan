#include "mmu.h"

#include <iostream>

namespace Mikan {
    MMU::MMU(Cartridge& cartridge) : cartridge(cartridge) {
        // Set default values
        this->set(0xff05, 0x00);
        this->set(0xff06, 0x00);
        this->set(0xff07, 0x00);
        this->set(0xff10, 0x80);
        this->set(0xff11, 0xbf);
        this->set(0xff12, 0xf3);
        this->set(0xff14, 0xbf);
        this->set(0xff16, 0x3f);
        this->set(0xff16, 0x3f);
        this->set(0xff17, 0x00);
        this->set(0xff19, 0xbf);
        this->set(0xff1a, 0x7f);
        this->set(0xff1b, 0xff);
        this->set(0xff1c, 0x9f);
        this->set(0xff1e, 0xff);
        this->set(0xff20, 0xff);
        this->set(0xff21, 0x00);
        this->set(0xff22, 0x00);
        this->set(0xff23, 0xbf);
        this->set(0xff24, 0x77);
        this->set(0xff25, 0xf3);
        this->set(0xff26, 0xf1);
        this->set(0xff40, 0x91);
        this->set(0xff42, 0x00);
        this->set(0xff43, 0x00);
        this->set(0xff45, 0x00);
        this->set(0xff47, 0xfc);
        this->set(0xff48, 0xff);
        this->set(0xff49, 0xff);
        this->set(0xff4a, 0x00);
        this->set(0xff4b, 0x00);
    }

    uint8_t MMU::get(uint16_t address) {
        if (address >= 0x0000 && address <= 0x7fff) {
            return this->cartridge.get(address);
        } else if (address >= 0x8000 && address <= 0x9fff) {
            // TODO: GPU
            return 0x0;
        } else if (address >= 0xa000 && address <= 0xbfff) {
            return this->cartridge.get(address);
        } else if (address >= 0xc000 && address <= 0xcfff) {
            return this->wram[address - 0xc000];
        } else if (address >= 0xd000 && address <= 0xdfff) {
            return this->wram[address - 0xd000 + 0x1000 * this->wramBank];
        } else if (address >= 0xe000 && address <= 0xefff) {
            return this->wram[address - 0xe000];
        } else if (address >= 0xf000 && address <= 0xfdff) {
            return this->wram[address - 0xf000 + 0x1000 * this->wramBank];
        } else if (address >= 0xfe00 && address <= 0xfe9f) {
            // TODO: GPU
            return 0x0;
        } else if (address >= 0xfea0 && address <= 0xfeff) {
            return 0x0;
        } else if (address == 0xff00) {
            return this->joypad.get(address);
        } else if (address >= 0xff01 && address <= 0xff02) {
            return this->serial.get(address);
        } else if (address >= 0xff04 && address <= 0xff07) {
            return this->timer.get(address);
        } else if (address == 0xff0f) {
            return this->interruptFlag.data;
        } else if (address >= 0xff10 && address <= 0xff3f) {
            // TODO: APU
            return 0x00;
        } else if (address == 0xff4d) {
            uint8_t sp = this->speed == Speed::Double ? 0x80 : 0x00;
            uint8_t sh = this->shift ? 0x01 : 0x00;
            return sp | sh;
        } else if ((address >= 0xff40 && address <= 0xff45) || 
                   (address >= 0xff47 && address <= 0xff4b) || 
                    address == 0xff4f) {
            // TODO: GPU
            return 0x0;
        } else if (address >= 0xff51 && address <= 0xff55) {
            return this->hdma.get(address);
        } else if (address >= 0xff68 && address <= 0xff6b) {
            // TODO: GPU
            return 0x0;
        } else if (address == 0xff70) {
            return this->wramBank;
        } else if (address >= 0xff80 && address <= 0xfffe) {
            return this->hram[address - 0xff80];
        } else if (address == 0xffff) {
            return this->interruptEnable;
        } else {
            return 0x00;
        }
    }

    void MMU::set(uint16_t address, uint8_t value) {
        if (address >= 0x0000 && address <= 0x7fff) {
            this->cartridge.set(address, value);
        } else if (address >= 0x8000 && address <= 0x9fff) {
            // TODO: GPU
            return;
        } else if (address >= 0xa000 && address <= 0xbfff) {
            this->cartridge.set(address, value);
        } else if (address >= 0xc000 && address <= 0xcfff) {
            this->wram[address - 0xc000] = value;
        } else if (address >= 0xd000 && address <= 0xdfff) {
            this->wram[address - 0xd000 + 0x1000 * this->wramBank] = value;
        } else if (address >= 0xe000 && address <= 0xefff) {
            this->wram[address - 0xe000] = value;
        } else if (address >= 0xf000 && address <= 0xfdff) {
            this->wram[address - 0xf000 + 0x1000 * this->wramBank] = value;
        } else if (address >= 0xfe00 && address <= 0xfe9f) {
            // TODO: GPU
            return;
        } else if (address >= 0xfea0 && address <= 0xfeff) {
            return;
        } else if (address == 0xff00) {
            this->joypad.set(address, value);
        } else if (address >= 0xff01 && address <= 0xff02) {
            this->serial.set(address, value);
        } else if (address >= 0xff04 && address <= 0xff07) {
            this->timer.set(address, value);
        } else if (address >= 0xff10 && address <= 0xff3f) {
            // TODO: APU
            return;
        }else if (address == 0xff46) {
            // Writing to this register launches a DMA transfer from ROM or RAM to OAM memory (sprite attribute table)
            if (value > 0xf1) {
                std::cerr << "0xff46 has a maximum value of 241" << std::endl;
                exit(1);
            }
            uint16_t base = (uint16_t)value << 8;
            for (int i = 0; i <= 0xa0; i++) {
                this->set(0xfe00 + i, this->get(base + i));
            }
        } else if (address == 0xff4d) {
            this->shift = (value & 0x01) == 0x01;
        } else if ((address >= 0xff40 && address <= 0xff45) || 
                   (address >= 0xff47 && address <= 0xff4b) || 
                    address == 0xff4f) {
            // TODO: GPU
            return;
        } else if (address >= 0xff51 && address <= 0xff55) {
            this->hdma.set(address, value);
        } else if (address >= 0xff68 && address <= 0xff6b) {
            // TODO: GPU
            return;
        } else if (address == 0xff0f) {
            this->interruptFlag.data = value;
        } else if (address == 0xff70) {
            uint8_t set = value & 0x7;
            if (set == 0) {
                this->wramBank = 1;
                return;
            }
            this->wramBank = set;
        } else if (address >= 0xff80 && address <= 0xfffe) {
            this->hram[address - 0xff80] = value;
        } else if (address == 0xffff) {
            this->interruptEnable = value;
        }
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