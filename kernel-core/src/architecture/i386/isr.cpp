#include <kernel/isr.h>
#include <stdio.h>
#include <stdlib.h>
#include <kernel/io.h>
#include <kernel/tty.h>
#include <kernel/keyboard.h>

void isr_default_int(int id){

	switch(id){
		case 0:
			printf("Division by zero OMEGALUL\n");
			break;
		case 1:
			handle_keyboard();
			break;
		default:
			printf("Division by zero OMEGALUL\n");
			break;
	}

	outb(0x20,0x20);

}
void do_syscalls(void){
	printf("do_syscalls\n");

	outb(0x20,0x20);
	outb(0xA0,0x20);
}
void isr_schedule_int(void){
	static int tic = 0;
	static long int sec = 0;
		tic++;
		if (tic % 18 == 0) {
		sec++;
		char mres[20];
		int secs = sec % 60;
		int mins = sec / 60;

		itoa(mins, mres);
		char sres[20];
		itoa((int)secs, sres);
		tty::terminal_update_header(mres, 70);
		tty::terminal_update_header(":", 71);
		tty::terminal_update_header(sres, 72);
		if(secs < 10){
			tty::terminal_update_header("0", 72);
			tty::terminal_update_header(sres, 73);
		}
		//printf("A second has passed\n");
		tic = 0;
	}

	outb(0x20,0x20);
	outb(0xA0,0x20);
}

void isr_GP_exc(void)
{	
	printf("\n General protection fault!\n");
	printf("The kernel have to be killed!\n\n");
	__asm__ volatile ("hlt");

	outb(0x20,0x20);
	outb(0xA0,0x20);
}

void isr_PF_exc(void)
{
	printf("isr_PF_exc\n");
    /*
	u32 faulting_addr, code;
	u32 eip;
	struct page *pg;
	u32 stack;
 	asm(" 	movl 60(%%ebp), %%eax	\n \
    		mov %%eax, %0		\n \
		mov %%cr2, %%eax	\n \
		mov %%eax, %1		\n \
 		movl 56(%%ebp), %%eax	\n \
    		mov %%eax, %2"
		: "=m"(eip), "=m"(faulting_addr), "=m"(code));
	 asm("mov %%ebp, %0": "=m"(stack):);
	
	//io.print("#PF : %x \n",faulting_addr);
	
	//for (;;);
		if (arch.pcurrent==NULL)
			return;
			
		process_st* current=arch.pcurrent->getPInfo();

	if (faulting_addr >= USER_OFFSET && faulting_addr <= USER_STACK) {
		pg = (struct page *) kmalloc(sizeof(struct page));
		pg->p_addr = get_page_frame();
		pg->v_addr = (char *) (faulting_addr & 0xFFFFF000);
		list_add(&pg->list, &current->pglist);
		pd_add_page(pg->v_addr, pg->p_addr, PG_USER, current->pd);
	}
	else {
		io.print("\n");
		io.print("No autorized memory acces on : %p (eip:%p,code:%p)\n", faulting_addr,eip,  code);
		io.print("heap=%x, heap_limit=%x, stack=%x\n",kern_heap,KERN_HEAP_LIM,stack);
		
		if (arch.pcurrent!=NULL){
			io.print("The processus %s have to be killed !\n\n",(arch.pcurrent)->getName());
			(arch.pcurrent)->exit();
			schedule();
		}
		else{
			io.print("The kernel have to be killed !\n\n");
			asm("hlt");
		}
	}*/
	outb(0x20,0x20);
	outb(0xA0,0x20);
		
}