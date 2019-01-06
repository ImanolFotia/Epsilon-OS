#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/io.h>

#include <string.h>

size_t tty::terminal_row;
size_t tty::terminal_column;
uint8_t tty::terminal_color;
uint16_t* tty::terminal_buffer;

void tty::terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga::vga_entry_color(vga::VGA_COLOR_LIGHT_GREY, vga::VGA_COLOR_LIGHT_BLUE);
	terminal_buffer = vga::VGA_MEMORY;
	
	for(size_t y = 0; y < vga::VGA_HEIGHT; ++y)
		for(size_t x = 0; x < vga::VGA_WIDTH; ++x) 
			terminal_buffer[y * vga::VGA_WIDTH + x] = vga::vga_entry(' ', terminal_color);
			
	terminal_enable_cursor(true);
}

void tty::terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void tty::terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * vga::VGA_WIDTH + x;
	terminal_buffer[index] = vga::vga_entry(c, color);
	
}

void tty::terminal_putchar(char c) {
	unsigned char uc = c;
	if(c == '\n'){
		terminal_column = 0;
		terminal_row++;
	}
	else if(c == '\t'){
		terminal_column = 4;
	}
	else { 
		terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
		terminal_column++;
	}
	
	
	if (terminal_column >= vga::VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;
	}
		
	if (terminal_row >= vga::VGA_HEIGHT)
		terminal_row = 0;
		
	
}

void tty::terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
	
	terminal_move_cursor(terminal_column, terminal_row);
}

void tty::terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void tty::printk(const char* data)
{
	terminal_writestring(data);
}

void tty::terminal_enable_cursor(bool enable)
{
	if(enable){
		write_port(0x3D4, 0x0A);
		write_port(0x3D5, (read_port(0x3D5) & 0xC0) | 0);
		write_port(0x3D4, 0x0A);
		write_port(0x3D5, (read_port(0x3D5) & 0xE0) | 15);
	}
	else 
	{
		write_port(0x3D4, 0x0A);
		write_port(0x3D5, 0x20);
	}
}

void tty::terminal_move_cursor(int x, int y)
{
	uint16_t pos = y * vga::VGA_WIDTH + x;
	write_port(0x3D4, 0x0F);
	write_port(0x3D5, (uint8_t) (pos & 0xFF));
	write_port(0x3D4, 0x0E);
	write_port(0x3D5, (uint8_t) ( (pos >> 8) & 0xFF ) );
}
/*
#ifdef __cplusplus

}
#endif
*/
