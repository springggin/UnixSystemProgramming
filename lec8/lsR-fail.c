/*
  Version of ls -R with at most one argument

  Differs from standard ls -R in that it:
    - Does not sort
    - Handles subdirectories as we come across them, rather than
      doing as ls -R listing all entries in the current directory first

  John Sterling
 */

#include <stdio.h>      // printf, perror
#include <dirent.h>     // DIR, dirent
#include <stdlib.h>     // exit
#include <string.h>     // strcat, strcpy
#include <sys/stat.h>   // stat, ISDIR

void listDir(char* dirname);

int main(int argc, char **argv) {

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        exit(1);
    }

    char *dirname = ".";
    if (argc == 2) dirname = argv[1];

    listDir(dirname);
}

void listDir(char* dirname) {
    DIR *dirp;
    struct dirent *direntp;
    struct stat statBuf;
    
    fprintf(stderr, "Tracing: listDir(%s)\n", dirname);
        

    // Check that we have a directory
    if ( (dirp = opendir(dirname)) == NULL ) {
        fprintf(stderr, "%s: ", dirname);
        perror("Failed to open directory");
        exit(2);
    }

    // print names of directory entries and recurse down the tree.
    while ( (direntp = readdir(dirp)) != NULL ) {
        // Ignoring hidden files
        if (direntp->d_name[0] != '.') {
            printf("%s\n", direntp->d_name);
            if (lstat(direntp->d_name, &statBuf) == -1) {
                fprintf(stderr, "%s: ", direntp->d_name);
                perror("Failed to lstat");
            }
            if (S_ISDIR(statBuf.st_mode)) {
                printf("============\n");
                printf("Begin subdirectory\n");
                listDir(direntp->d_name);
                printf("End subdirectory\n");
                printf("============\n");
            }
        }
    }
    closedir(dirp);
}
