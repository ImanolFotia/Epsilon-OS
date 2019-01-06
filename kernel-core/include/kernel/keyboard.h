#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <stddef.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define ENTER_KEY_CODE 0x1C


struct idt_pointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

void idt_init(void);
void kb_init(void);
void handler_main(void);

#endif //_KEYBOARD_H
