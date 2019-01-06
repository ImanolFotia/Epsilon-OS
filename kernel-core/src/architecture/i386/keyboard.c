#include <kernel/keyboard.h>
#include <kernel/io.h>
#include <kernel/tty.h>
#include <kernel/keyboard_map.h>
#include <stdbool.h>


extern void keyboard_handler_int(void);
extern void idt_load(struct idt_pointer);

void idt_init(void)
{
	
}


void kb_init(void)
{
	/*Re-map PIC*/
	
    outb(0x20, 0x11); 
    write_port(0xA0, 0x11);
    write_port(0x21, 0x20);
    write_port(0xA1, 0x28);
    write_port(0x21, 0x04);
    write_port(0xA1, 0x02);
    write_port(0x21, 0x01);
    write_port(0xA1, 0x01);
    write_port(0x21, 0x0);
	write_port(0xA1, 0x0);
	
	write_port(0x21, 0xFD);
}


void handler_main(void)
{
	unsigned char status;
	char keycode;

	status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;

		if(keycode == ENTER_KEY_CODE) {
			printf("\n");
			return;
		}
		printf(/*keyboard_map[(unsigned char) keycode]*/"A");
	}
	
	/* write EOI */
	write_port(0x20, 0x20);
}

