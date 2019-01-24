#include <kernel/gdt.h>
#include <kernel/io.h>
#include <stdio.h>

idtdesc gdt::kidt[IDTSIZE];  /* IDT table */
int_desc gdt::intt[IDTSIZE]; /* Interruptions functions tables */
gdtdesc gdt::kgdt[GDTSIZE];  /* GDT */

void gdt::init_idt_desc(uint16_t select, uint32_t offset, uint16_t type, idtdesc *desc)
{
    desc->offset0_15 = (offset & 0xffff);
    desc->select = select;
    desc->type = type;
    desc->offset16_31 = (offset & 0xffff0000) >> 16;
    return;
}

void gdt::init_gdt_desc(uint32_t base, uint32_t limit, uint8_t acces, uint8_t other, gdtdesc *desc)
{
    desc->lim0_15 = (limit & 0xffff);
    desc->base0_15 = (base & 0xffff);
    desc->base16_23 = (base & 0xff0000) >> 16;
    desc->acces = acces;
    desc->lim16_19 = (limit & 0xf0000) >> 16;
    desc->other = (other & 0xf);
    desc->base24_31 = (base & 0xff000000) >> 24;
    return;
}

void gdt::init_gdt(void)
{
    default_tss.debug_flag = 0x00;
    default_tss.io_map = 0x00;
    default_tss.esp0 = 0x1FFF0;
    default_tss.ss0 = 0x18;

    /* initialize gdt segments */
    init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
    init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]); /* code */
    init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]); /* data */
    init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);     /* stack */

    init_gdt_desc(0x0, 0xFFFFF, 0xFF, 0x0D, &kgdt[4]); /* ucode */
    init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, &kgdt[5]); /* udata */
    init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, &kgdt[6]);     /* ustack */

    init_gdt_desc((uint32_t)&default_tss, 0x67, 0xE9, 0x00, &kgdt[7]); /* tss descriptor */

    /* initialize the gdtr structure */
    kgdtr.limit = GDTSIZE * 8;
    kgdtr.base = GDTBASE;

    /* copy the gdtr to its memory area */
    memcpy((char *)kgdtr.base, (char *)kgdt, kgdtr.limit);

    /* load the gdtr registry */
    __asm__("lgdtl %0" ::"m"(kgdtr));

    /* initiliaz the segments */
    __asm__("   movw $0x10, %ax	\n \
                movw %ax, %ds	\n \
                movw %ax, %es	\n \
                movw %ax, %fs	\n \
                movw %ax, %gs	\n \
                ljmp $0x08, $next	\n \
                next:		\n");
}

extern "C" {
extern void _asm_int_0();
extern void _asm_int_1();
extern void _asm_syscalls();
extern void _asm_exc_GP(void);
extern void _asm_exc_PF(void);
extern void _asm_schedule();
}
void gdt::init_idt()
{
    /* Init irq */
    int i;
    for (i = 0; i < IDTSIZE; i++)
        init_idt_desc(0x08, (uint32_t)_asm_schedule, INTGATE, &kidt[i]); //

    /* Vectors  0 -> 31 are for exceptions */
    init_idt_desc(0x08, (uint32_t)_asm_exc_GP, INTGATE, &kidt[13]); /* #GP */
    init_idt_desc(0x08, (uint32_t)_asm_exc_PF, INTGATE, &kidt[14]); /* #PF */

    init_idt_desc(0x08, (uint32_t)_asm_schedule, INTGATE, &kidt[32]);
    init_idt_desc(0x08, (uint32_t)_asm_int_1, INTGATE, &kidt[33]);

    init_idt_desc(0x08, (uint32_t)_asm_syscalls, TRAPGATE, &kidt[48]);
    init_idt_desc(0x08, (uint32_t)_asm_syscalls, TRAPGATE, &kidt[128]); //48

    kidtr.limit = IDTSIZE * 8;
    kidtr.base = IDTBASE;

    /* Copy the IDT to the memory */
    memcpy((char *)kidtr.base, (char *)kidt, kidtr.limit);

    /* Load the IDTR registry */
    __asm__("lidtl %0" ::"m"(kidtr));
}

void gdt::init_pic(void)
{
    /* Initialization of ICW1 */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    /* Initialization of ICW2 */
    outb(0x21, 0x20);    /* start vector = 32 */
    outb(0xA1, 0x70);    /* start vector = 96 */

    /* Initialization of ICW3 */
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    /* Initialization of ICW4 */
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    /* mask interrupts */
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    /*Finally, enable interrupts */
	__asm__ ("sti");
}
