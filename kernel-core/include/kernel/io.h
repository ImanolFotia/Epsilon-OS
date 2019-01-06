#ifndef _IO_H
#define _IO_H

#include <stddef.h>
#include <stdio.h>
/*Low level functions used to read ports*/

#define outb(x, y) write_port(x, y)
#define inb(x) read_port(x)

static inline uint16_t read_port(uint16_t port)
{
	uint8_t val;
	__asm__ __volatile__ ("inb %1, %0" : "=a"(val) : "Nd"(port));
	return val;
}

static inline void write_port(uint16_t port, uint8_t data)
{
	__asm__ __volatile__ ("outb %1, %0" :: "Nd" (port), "a" (data));
}

#endif //_IO_H
