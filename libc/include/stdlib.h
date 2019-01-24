#ifndef STDLIB_H
#define STDLIB_H
 
#include <sys/cdefs.h>
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
__attribute__((__noreturn__))
void abort(void);

int atoi(const char**);
char* itoa(int val, char res[]);
const char* ftoa(float val, int);

char* malloc(size_t len);
 
#ifdef __cplusplus
}
#endif

#endif //STDLIB_H
