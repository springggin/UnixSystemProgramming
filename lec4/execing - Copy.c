/*
  execing
  Trying to use execv to run "ls -l"
  Result?  Why?
 */

#include <stdio.h>
#include <unistd.h>

int main() {
    char* argv[] = {"ls", "-l", NULL};
    execv(argv[0], argv);
    perror("execv must have failed or we wouldn't be here");
    return 0;
}
