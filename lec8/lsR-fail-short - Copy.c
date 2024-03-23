/*
  Version of ls -R with at most one argument

  fails

  John Sterling
 */

#include <stdio.h>      // printf, perror
#include <dirent.h>     // DIR, dirent
#include <stdlib.h>     // exit
#include <string.h>     // strcat, strcpy
#include <sys/stat.h>   // stat, ISDIR

void listDir(char* dirname);

int main(int argc, char **argv) {
    if (argc == 1) listDir(".");
    else listDir(argv[1]);
}

void listDir(char* dirname) {
    struct dirent *direntp;
    struct stat statBuf;
    DIR *dirp = opendir(dirname);
    while ( (direntp = readdir(dirp)) != NULL ) {
        if (direntp->d_name[0] != '.') {
            printf("%s\n", direntp->d_name);
            lstat(direntp->d_name, &statBuf);
	    //if ((statBuf.st_mode & S_IFMT) == S_IFDIR) {
            if (S_ISDIR(statBuf.st_mode)) {
                listDir(direntp->d_name);
            }}}
    closedir(dirp);
}
