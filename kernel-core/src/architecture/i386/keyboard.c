#include <kernel/keyboard.h>
#include <kernel/io.h>
#include <kernel/tty.h>
#include <kernel/keyboard_map.h>
#include <stdbool.h>
#include <stddef.h>

static bool LCTRL_PRESSED;
static bool RCTRL_PRESSED;
static bool LSHIFT_PRESSED;
static bool RSHIFT_PRESSED;
static bool LALT_PRESSED;
static bool RALT_PRESSED;

void keyboard::handle_keyboard()
{
	unsigned char status;
	char keycode;

	uint8_t scancode;
	scancode = inb(0x60);

	if (scancode == 0x2A || scancode == 0x36) // L Shift
	{
		//printf("Shift pressed ");
	}
	if (scancode == 0x38 || scancode == 0xE0) //ALT
	{
		//printf("Alt pressed ");
	}
	if (scancode == 0x1D) //crtl
	{
		//printf("Ctrl pressed ");
	}
	else
	{
		if (scancode < 0x80)
			printf("%c", (int)keyboard_map[scancode]);
	}
}
