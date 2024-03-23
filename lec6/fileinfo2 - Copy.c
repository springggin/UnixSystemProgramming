/* 
   fileinfo
   John Sterling

   Not handling set uid, set gid or "sticky".
 */

#include <stdio.h>     // printf
#include <string.h>    // strlen
#include <stdlib.h>    // exit
#include <sys/stat.h>  // struct stat
#include <sys/types.h> // mode_t
#include <pwd.h>       // struct passwd
#include <grp.h>       // getgrgid
#include <time.h>      // ctime

void printmode(mode_t mode);

int main(int argc, char *argv[]) {
    struct stat info;

    if (argc != 2) {
        fprintf(stderr, "usage: %s pathname\n", argv[0]);
        exit(1);
    }

    stat(argv[1], &info);
  
    printmode(info.st_mode);
    printf("  links: %hu\n", info.st_nlink);                  // # links     
    printf("   user: %s\n", getpwuid(info.st_uid)->pw_name);  // user id     
    printf("  group: %s\n", getgrgid(info.st_gid)->gr_name);  // group id    
    printf("   size: %d\n", (int)info.st_size);               // file size   
    printf("   blocks: %d\n", (int)info.st_blocks);           // file blocks   
    printf("modtime: %.12s\n", 4+ctime(&info.st_mtime));      // modified    
    printf("   name: %s\n", argv[1]);                         // filename    

    return 0;
}

void printmode(mode_t mode) {
    char result[] = "----------";
  
    // File Type
    if ((mode & S_IFMT) == S_IFREG) result[0] = '-';       // regular
    else if ((mode & S_IFMT) == S_IFDIR) result[0] = 'd';  // directory
    else if ((mode & S_IFMT) == S_IFLNK) result[0] = 'l' ; // symbolic link
    else if ((mode & S_IFMT) == S_IFSOCK) result[0] = 's'; // socket
    else if ((mode & S_IFMT) == S_IFBLK) result[0] = 'b';  // block-special
    else if ((mode & S_IFMT) == S_IFCHR) result[0] = 'c';  // character-special
    else if ((mode & S_IFMT) == S_IFIFO) result[0] = 'p';  // FIFO
    else result[0] = '?';  // Unknown file type

    if (mode & S_IRUSR) result[1] = 'r';
    if (mode & S_IWUSR) result[2] = 'w';
    if (mode & S_IXUSR) result[3] = 'x';
    if (mode & S_IRGRP) result[4] = 'r';
    if (mode & S_IWGRP) result[5] = 'w';
    if (mode & S_IXGRP) result[6] = 'x';
    if (mode & S_IROTH) result[7] = 'r';
    if (mode & S_IWOTH) result[8] = 'w';
    if (mode & S_IXOTH) result[9] = 'x';
    printf("   mode: %s\n", result);
}
