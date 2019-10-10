#pragma once

#include <stddef.h>

char* kalloc(size_t len);
int kfree(char* addr);