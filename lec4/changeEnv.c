/* changeenv.c  - shows how to change the environment
 *                note: calls "env" to display its new settings
 *
 *                NB: gcc expects you to use the return value
 *                Compile with -Wno-unused-result to disable warning from -Wall.
 */

#include	<stdio.h>
#include	<stdlib.h>  // system

extern char **environ;

int main() {
  
    char *table[3];
    table[0] = "TERM=vt100";	// fill the new environment array
    table[1] = "HOME=/on/the/range";
    table[2] = 0;

    puts("Running env");
    system("env");	// Uses shell to run env command
    puts("========================");
    puts("Changing environ");
    environ = table;	// point to that table
    puts("Running env");
    system("env");
}
