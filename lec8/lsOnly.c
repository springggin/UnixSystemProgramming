/*
  ls with no options and at most one argument
  jbs
 */

#include <stdio.h>   // fprintf, stderr, perror, printf
#include <dirent.h>  // DIR, opendir, dirent, readdir, closedir
#include <stdlib.h>  // EXIT_FAILURE

int main(int argc, char **argv) {

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        return EXIT_FAILURE;
    }

    DIR *dirp;
    char *dirname = ".";
    if (argc == 2) dirname = argv[1];

    if ((dirp = opendir(dirname)) == NULL) {
        perror("Failed to open directory");
        return EXIT_FAILURE;
    }

    struct dirent *direntp;
    // Should be setting / testing errno!!!
    while ((direntp = readdir(dirp)) != NULL) {
        if (direntp->d_name[0] != '.') {
            printf("%s\n", direntp->d_name);
        }
    }

    closedir(dirp);
}
