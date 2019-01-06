#include <kernel/vga.h>

//Set up a simple VGA driver using BIOS' 80x25 columns
const size_t vga::VGA_WIDTH = 80;
const size_t vga::VGA_HEIGHT = 25;

uint16_t* const vga::VGA_MEMORY = (uint16_t*) 0xB8000;

uint8_t vga::vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t vga::vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}
