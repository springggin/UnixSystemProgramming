/* 
   displayPS1
   John Sterling

   Demonstrates the use of getenv

 */
#include	<stdio.h>   // puts
#include	<stdlib.h>  // getenv

extern char **environ;

int main() {
     // retrieve and display the PS1 variable
    char* s = getenv("PS1");
    if (s) puts(s);
    else puts("No PS1");

    // retrieve and display the PATH variable
    s = getenv("PATH");
    if (s) puts(s);
    else puts("No PATH");   
}
