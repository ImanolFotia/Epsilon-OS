#pragma once

#include <stddef.h> // uintx_t types
#include <kernel/tss.h>
#include <string.h>

#define GDTBASE 0x00000800
#define IDTSIZE 0xFF
#define GDTSIZE 0xFF

#define IDTBASE 0x00000000 
#define GDTBASE 0x00000800 

#define INTGATE 0x8E00
#define TRAPGATE 0xEF00

extern "C" {

    typedef void (*int_desc)(void);

    struct idtdesc
    {
        uint16_t offset0_15;
        uint16_t select;
        uint16_t type;
        uint16_t offset16_31;
    } __attribute__((packed));

    struct gdtr
    {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed));

    struct gdtdesc
    {
        uint16_t lim0_15;
        uint16_t base0_15;
        uint8_t base16_23;
        uint8_t acces;
        uint8_t lim16_19 : 4;
        uint8_t other : 4;
        uint8_t base24_31;
    } __attribute__((packed));

    struct idtr
    {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed));


    static gdtr kgdtr; /* GDTR */
    static idtr kidtr; /* IDTR registry */


class gdt
{
  public:
    gdt() = default;
    ~gdt() {}

    static void init_idt_desc(uint16_t select, uint32_t offset, uint16_t type, idtdesc *desc);

    static void init_gdt_desc(uint32_t base, uint32_t limit, uint8_t acces, uint8_t other, gdtdesc *desc);

    static void init_gdt();

    static void init_idt();

    static void init_pic();

  public:

    static idtdesc kidt[IDTSIZE];  /* IDT table */
    static int_desc intt[IDTSIZE]; /* Interruptions functions tables */
    static gdtdesc kgdt[GDTSIZE];  /* GDT */

};

}
