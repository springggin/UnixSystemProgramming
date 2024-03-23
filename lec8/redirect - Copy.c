/*
  redirect.c
  demonstrates redirection of standard input
  by first closing standard input
  and then opening a file.

  Note that error checking was omitted for readability.
  You would, of course, provide it!
 */

#include <unistd.h> // close
#include <fcntl.h>  // open
#include <stdlib.h> // exit

const int BUFFSIZE = 100;

int main() {
    char line[BUFFSIZE];

    // read from the console and print to the console
    int n = read(STDIN_FILENO, line, BUFFSIZE-1);
    line[n] = '\n';
    write(STDOUT_FILENO, line, n+1);
  
    // redirect input by closing standard input and opening the file
    close(STDIN_FILENO);                       // close standard input
    open("/etc/passwd", O_RDONLY);  // Redirecting standard input to passwd

    // again read from standard input, now the file, 
    // and print to the console. Same code as in the beginning.
    n = read(STDIN_FILENO, line, BUFFSIZE-1);
    line[n] = '\n';
    write(STDOUT_FILENO, line, n+1);
}
