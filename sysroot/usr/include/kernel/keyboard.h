#pragma once

#include <stddef.h>

#define ENTER_KEY_CODE 0x1C

class keyboard {

public:
	keyboard(){}
	~keyboard(){}
	
	void handle_keyboard(); 

};
