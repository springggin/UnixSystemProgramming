/*
  bad_longjmp.c

  Demonstrates how NOT to use setjmp / longjmp work.

  Interestingly it mostly "sort of" works. :-)
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf buf;

void larry() { 
    printf("Larry\n");
    int some_val = 6;
    longjmp(buf, 17);
    fprintf(stderr, "larry after longjmp. Should never get here\n");
    ++some_val; // just to prevent warning about not using some_val
}

void moe() {
    printf("Moe\n");
    int local = 42;
    switch (setjmp(buf)) {
    case 0:
	puts("Established jump buffer");
	break;
    case 17:
	puts("Wow! Moe back from a long jump! val = 17");
	break;
    }
    printf("Moe out: local == %d\n", local);
}

int main() {
    moe();
    larry();
    puts("done");
}
