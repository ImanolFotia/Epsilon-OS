#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/memory.h>


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


void reverse(char s[])
 {
     int i = 0, j = 0;
     char c = 0;
     for (i = 0, j = strlen((char*)s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

char* itoa(int val, char res[])
{
     int i = 0, sign = 0;
 	 char s[20];
     if ((sign = val) < 0)  /* record sign */
         val = -val;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = val % 10 + '0';   /* get next digit */
     } while ((val /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';

     reverse(s);
     s[i] = '\0';
     memcpy(res, s, 20);
     return &s[0];
}


const char* ftoa(float val, int afterpoint)
{
    char sign;
    char* output;
    int index = 0;
    if((sign = (int)val) < 0) {
        val = -val;
        output[index++] = '-';
    }
    int left = (int)val;
    float right = val - (float)left;

    char* leftc;
    itoa(left, leftc);
    int leftcl = strlen(leftc);

    for(int i = 0; i < leftcl; i++) {
        if(leftc[i] != '\0') {
            output[index++] = leftc[i];
        }
    }

    output[index++] = '.';

    if(afterpoint != 0){
        int righti  = right * pow(10, afterpoint);
        char* rightc;
        itoa(right, rightc);
        int rightcl = strlen(rightc);

        for(int i = 0; i < rightcl; i++) {
            if(rightc[i] != '\0') {
                output[index++] = rightc[i];
            }
    }
    }

    output[index++] = 'f';
    output[index++] = '\0';
    return output;
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

char* malloc(size_t len)
{
    return kalloc(len);
} 
