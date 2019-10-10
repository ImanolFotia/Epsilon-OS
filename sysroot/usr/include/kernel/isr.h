#pragma once

extern "C" {

void isr_default_int(int);
void do_syscalls(void); 
void isr_schedule_int(void);
void isr_PF_exc(void);
void isr_GP_exc(void);

}