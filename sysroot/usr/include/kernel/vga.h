#pragma once

#include <stddef.h>

class vga {

public:
	vga() = default;
	~vga(){}
	//Set up a simple VGA driver using BIOS' 80x25 columns
	static const size_t VGA_WIDTH;
	static const size_t VGA_HEIGHT;

	static uint16_t* const VGA_MEMORY;


	enum vga_color {
		VGA_COLOR_BLACK = 0,
		VGA_COLOR_BLUE = 1,
		VGA_COLOR_GREEN = 2,
		VGA_COLOR_CYAN = 3,
		VGA_COLOR_RED = 4,
		VGA_COLOR_MAGENTA = 5,
		VGA_COLOR_BROWN = 6,
		VGA_COLOR_LIGHT_GREY = 7,
		VGA_COLOR_DARK_GREY = 8,
		VGA_COLOR_LIGHT_BLUE = 9,
		VGA_COLOR_LIGHT_GREEN = 10,
		VGA_COLOR_LIGHT_CYAN = 11,
		VGA_COLOR_LIGHT_RED = 12,
		VGA_COLOR_LIGHT_MAGENTA = 13,
		VGA_COLOR_LIGHT_BROWN = 14,
		VGA_COLOR_WHITE = 15,
	};

	static uint8_t vga_entry_color(vga_color fg, vga_color bg);

	static uint16_t vga_entry(unsigned char uc, uint8_t color);

};

