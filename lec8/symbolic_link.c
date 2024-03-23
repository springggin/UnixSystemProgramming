/*
  Shortened version of program from man page for readlink
 */

//#include <sys/types.h>
#include <sys/stat.h> // lstat, stat
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc
#include <unistd.h>   // readlink

int main(int argc, char *argv[]) {
    struct stat sb;
    lstat(argv[1], &sb);
    char *linkname = malloc(sb.st_size + 1);
    ssize_t r = readlink(argv[1], linkname, sb.st_size + 1);
    linkname[r] = '\0';
    printf("'%s' points to '%s'\n", argv[1], linkname);
}
