/*
  showEnv.c
  John Sterling

  Displays the environment
 */

#include <stdio.h>

extern char **environ;

int main() {

    puts("==============");
    
    // Loop over the environment using an index
    // Note that we don't know how large the environment array is,
    // so we depend on the sentinel value NULL to tell us when we are done.
    for (int index = 0; environ[index] != NULL; ++index) {
        puts(environ[index]);
    }

    puts("==============");

    // Loop over the environment using a pointer
    // Remember that environ is a pointer to an array of pointers.
    for (char **p = environ; *p; ++p) {
        puts(*p);
    }

    puts("==============");

}
