#pragma once
#include <stdbool.h>

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
#define restrict __restrict__
extern "C" {
#endif

int printf(const char* __restrict,...);
int puts(const char*);
int putchar(int);

#ifdef __cplusplus
}
#endif

