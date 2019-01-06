//#include <stdio.h>
#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/keyboard.h>

#ifdef __cplusplus
extern "C" {
#endif
void kernel_main(void) 
{
	tty::terminal_initialize();
	printf("Hello from the kernel!\n");
 		
 	char* a = "asd";
 	float b = 1.5 + 5.3;
 	printf("\nString: %s is in memory address: %d\n", a, *a);
 	printf("1.5 + 5.3 is: %d\n", b);
 	tty::printk("root@imanol / $ ");
 	
	idt_init();
	kb_init();
 	
 	while(1) __asm__ ("hlt");
}
#ifdef __cplusplus
}
#endif
