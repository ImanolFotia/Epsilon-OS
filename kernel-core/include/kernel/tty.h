#pragma once

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
class tty {
public:
	tty() = default;
	~tty(){}
	
	static void terminal_initialize(void);
	static void terminal_putchar(char c);
	static void terminal_write(const char* data, size_t size);
	static void terminal_writestring(const char* data);
	static void terminal_move_cursor(int x, int y);
	static void terminal_enable_cursor(bool);
	static void printk(const char*);
	static void terminal_setcolor(uint8_t color);
	static void terminal_putentryat(unsigned char,uint8_t,size_t,size_t);
	
private:
	static size_t terminal_row;
	static size_t terminal_column;
	static uint8_t terminal_color;
	static uint16_t* terminal_buffer;
};
#ifdef __cplusplus
}
#endif

