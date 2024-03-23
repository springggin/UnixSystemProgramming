/*
  execing-2
  Using execvp to run "ls -l"
  Result?  Why?
 */

#include <stdio.h>
#include <unistd.h>

int main() {
    char* argv[] = {"ls", "-l", NULL};
    execvp(argv[0], argv);
    //execlp("ls", "ls", "-l", NULL);
    perror("execvp must have failed or we wouldn't be here");
    return 0;
}
