//#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>

#ifdef __cplusplus
extern "C" {
#endif
void kernel_main(void) 
{
	tty::terminal_initialize();
	tty::terminal_update_header("Epsilon OS (i386-elf)", 1);
	tty::printk("Created by Imanol Fotia (www.imanolfotia.com)\n\n");
	tty::printk("Distributed under MIT License\n\n");

	tty::printk("Initializing TTY...\t");
	tty::printk("[OK]\n");
	tty::printk("Initializing GDT...\t");
	gdt::init_gdt();
	tty::printk("[OK]\n");
	tty::printk("Initializing IDT...\t");
	gdt::init_idt();
	tty::printk("[OK]\n");
	tty::printk("Initializing PIC...\t");
	gdt::init_pic();
	tty::printk("[OK]\n");
	tty::printk("Ready\n\n");
 	tty::printk("~@kernel $ ");

 	while(1){} __asm__ ("hlt");
}
#ifdef __cplusplus
}
#endif
