/* 
   fileinfo.c
   Display some information from the inode
   Uses stat function and struct stat
 */
#include <stdio.h>	    // printf, fprintf
#include <sys/stat.h>	// struct stat
#include <stdlib.h>	    // exit

#define FORMAT_ERROR 1

int main(int argc, char *argv[]) {
    struct stat info;

    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(FORMAT_ERROR);
    }

    stat(argv[1], &info);
    printf("    mode: %o\n",  info.st_mode);         // type + mode 
    printf("   links: %u\n",  info.st_nlink);        // # links     
    printf(" user id: %d\n",  info.st_uid);          // user id     
    printf("group id: %d\n",  info.st_gid);          // group id    
    printf("    size: %d\n",  (int)info.st_size);    // file size   
    printf(" modtime: %d\n",  (int)info.st_mtime);   // modified    
    printf("    name: %s\n",  argv[1]);              // filename    

    return 0;
}

