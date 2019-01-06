#include <stdio.h>
#include <stdlib.h>
#include <string.h>
__attribute__((__noreturn__))
void abort(void) {
#if defined(__is_libk)
	// TODO: Add proper kernel panic.
	printf("kernel: panic: abort()\n");
#else
	// TODO: Abnormally terminate the process as if by SIGABRT.
	printf("abort()\n");
#endif
	while (1) { }
	__builtin_unreachable();
}


char* reverse(const char* s)
 {
     int i, j;
     char c;
     char* ss = (char*) s;
     for (i = 0, j = strlen(ss)-1; i<j; i++, j--) {
         c = ss[i];
         ss[i] = ss[j];
         ss[j] = c;
     }
     return ss;
 }

const char* itoa(int val)
{
     int i, sign;
 	 char* s = {0};
     if ((sign = val) < 0)  /* record sign */
         val = -val;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = val % 10 + '0';   /* get next digit */
     } while ((val /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     s = reverse(s);
     return s;
}

static inline bool _is_digit(char ch)
{
  return (ch >= '0') && (ch <= '9');
}

int atoi(const char** s)
{
  unsigned int i = 0U;
  while (_is_digit(**s)) {
    i = i * 10U + (unsigned int)(*((*s)++) - '0');
  }
  return i;
}
 
