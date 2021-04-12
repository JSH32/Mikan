#pragma once

#include <cinttypes>

namespace Mikan {
    /**
     * LCDC is the main LCD Control register. 
     * Its bits toggle what elements are displayed on the screen, and how.
     */
    class Lcdc {
    public:
        uint8_t data = 0b01001000;

        /**
         * LCDC.7 - LCD Display Enable
         * This bit controls whether the LCD is on and the PPU is active. Setting it to 0 turns both off, which grants
         * immediate and full access to VRAM, OAM, etc.
         */
        bool bit7();

        /**
         * LCDC.6 - Window Tile Map Display Select
         * This bit controls which background map the Window uses for rendering. When it's reset, the $9800 tilemap is used,
         * otherwise it's the $9C00 one.
         */
        bool bit6();

        /**
         * LCDC.5 - Window Display Enable
         * This bit controls whether the window shall be displayed or not. (TODO : what happens when toggling this
         * mid-scanline ?) This bit is overridden on DMG by bit 0 if that bit is reset.
         * Note that on CGB models, setting this bit to 0 then back to 1 mid-frame may cause the second write to be ignored.
         */
        bool bit5();

        /**
         * LCDC.4 - BG & Window Tile Data Select
         * This bit controls which addressing mode the BG and Window use to pick tiles.
         * Sprites aren't affected by this, and will always use $8000 addressing mode.
         */
        bool bit4();

        /**
         * LCDC.3 - BG Tile Map Display Select
         * This bit works similarly to bit 6: if the bit is reset, the BG uses tilemap $9800, otherwise tilemap $9C00.
         */
        bool bit3();

        /**
         * LCDC.2 - OBJ Size
         * This bit controls the sprite size (1 tile or 2 stacked vertically).
         * Be cautious when changing this mid-frame from 8x8 to 8x16 : "remnants" of the sprites intended for 8x8 could
         * "leak" into the 8x16 zone and cause artifacts.
         */
        bool bit2();

        /**
         * LCDC.1 - OBJ Display Enable
         * This bit toggles whether sprites are displayed or not.
         * This can be toggled mid-frame, for example to avoid sprites being displayed on top of a status bar or text box.
         * (Note: toggling mid-scanline might have funky results on DMG? Investigation needed.)
         */
        bool bit1();

        /**
         * LCDC.0 - BG/Window Display/Priority
         * LCDC.0 has different meanings depending on Gameboy type and Mode:
         * Monochrome Gameboy, SGB and CGB in Non-CGB Mode: BG Display
         * When Bit 0 is cleared, both background and window become blank (white), and the Window Display Bit is ignored in
         * that case. Only Sprites may still be displayed (if enabled in Bit 1).
         * CGB in CGB Mode: BG and Window Master Priority
         * When Bit 0 is cleared, the background and window lose their priority - the sprites will be always displayed on
         * top of background and window, independently of the priority flags in OAM and BG Map attributes.
         */
        bool bit0();
    };
}