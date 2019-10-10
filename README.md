# Epsilon-OS
32-bit, protected mode, i386 Kernel written in C++

## Overview
Epsilon OS aims to a be a lightweight microkernel for the x86 architecture
Only IO, interrupts, and threading will be implemented in kernel-mode,
All other components, such a Virtual File Systems will be implemented in user space.

## Roadmap
  * PIC implemented
  * Basic interruption handler implemented, so it doesn't triple fault
  * GDT implemented
  * Basic TTY implemented for basic debugging
  * C library implemented as needed, far from decent
  
## TODO:
  * Implement a proper libc library
  * Enable paging and framing
  * Implement multitasking
  * Implement a heap
  * Enable user mode
  * Filesystem
  
## Misc
  * Implement a user interface
  * Different graphics modes
  * TCP stack and networking
  * Sound support
