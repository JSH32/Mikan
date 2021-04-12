#pragma once

#include <cinttypes>

#include "../memory.h"

namespace Mikan {
    enum class HdmaMode {
        /**
         * When using this transfer method, all data is transferred at once. The execution of the program is halted until
         * the transfer has completed. Note that the General Purpose DMA blindly attempts to copy the data, even if the
         * CD controller is currently accessing VRAM. So General Purpose DMA should be used only if the Display is disabled,
         * or during V-Blank, or (for rather short blocks) during H-Blank. The execution of the program continues when the
         * transfer has been completed, and FF55 then contains a value of FFh.
         */
        Gdma,

        /**
         * The H-Blank DMA transfers 10h bytes of data during each H-Blank, ie. at LY=0-143, no data is transferred during
         * V-Blank (LY=144-153), but the transfer will then continue at LY=00. The execution of the program is halted
         * during the separate transfers, but the program execution continues during the 'spaces' between each data block.
         * Note that the program should not change the Destination VRAM bank (FF4F), or the Source ROM/RAM bank (in case
         * data is transferred from bankable memory) until the transfer has completed! (The transfer should be paused as
         * described below while the banks are switched) Reading from Register FF55 returns the remaining length (divided
         * by 10h, minus 1), a value of 0FFh indicates that the transfer has completed. It is also possible to terminate
         * an active H-Blank transfer by writing zero to Bit 7 of FF55. In that case reading from FF55 will return how many
         * $10 "blocks" remained (minus 1) in the lower 7 bits, but Bit 7 will be read as "1". Stopping the transfer
         * doesn't set HDMA1-4 to $FF.
         */
        Hdma
    };

    class Hdma : public Memory {
    public:
        HdmaMode mode = HdmaMode::Gdma;

        /**
         * These two registers specify the address at which the transfer will read data from. Normally, this should be
         * either in ROM, SRAM or WRAM, thus either in range 0000-7FF0 or A000-DFF0. [Note : this has yet to be tested on
         * Echo RAM, OAM, FEXX, IO and HRAM]. Trying to specify a source address in VRAM will cause garbage to be copied.
         * The four lower bits of this address will be ignored and treated as 0. 
         */
        uint16_t source = 0x0000;

        /**
         * These two registers specify the address within 8000-9FF0 to which the data will be copied. Only bits 12-4 are
         * respected; others are ignored. The four lower bits of this address will be ignored and treated as 0.
         */
        uint16_t destination = 0x8000;

        uint8_t remainder = 0x00;

        bool active = false;

        // Memory implementation
        uint8_t get(uint16_t address);
        void set(uint16_t address, uint8_t value);
    };
}