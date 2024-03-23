/*
  ls -l for a single directory
 */

#include <stdio.h>      // printf, perror
#include <dirent.h>   	// DIR, dirent, opendir, closedir, readdir
#include <string.h>     // strlen, strcpy
#include <sys/stat.h>	// struct stat
#include <pwd.h>	// getpwuid
#include <grp.h>	// getgrgid
#include <time.h>	// ctime
#include <limits.h>	// PATH_MAX
#include <stdlib.h>	// exit

enum FLAGS { NOFLAG = 0, LFLAG = 1 };
void decode_mode(mode_t mode, char* result);
void display_entry(char* direntp, char*);
void showDir(char* dirname, int flags);

int main(int argc, char **argv) {

  // Check options
  // Only actually handling -l for now
  int flags = NOFLAG;
  int index;
  for (index = 1; index < argc && argv[index][0] == '-'; ++index) {
    if (argv[index][1] == 'l') flags |= LFLAG;
  }

  // if (argc > 2) {
  //   fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
  //   return 1;
  // }

  char dirname[PATH_MAX] = ""; // Will hol
  if (argv[index] == NULL) {
    strcpy(dirname, ".");
  }
  else strcpy(dirname, argv[index]); //dir name 에다가 input값 넣음. 
  showDir(dirname, flags);


}

// void printmode(mode_t mode) {
//   char result[] = "----------";
//   const int len = strlen(result);
//   const char permissions[] = "rwxrwxrwx";
  
//   for (int mask = 1, index = 0; mask < 01000; mask <<= 1, ++index) {
//     if (mode & mask) {
//       result[len-1-index] = permissions[8-index];
//     }
//   }
//   printf("   mode: %s\n", result);
// }

void decode_mode(mode_t mode, char* result) {
  //  char result[] = "----------";
  
  if ((mode & S_IFMT) == S_IFDIR) result[0] = 'd';
  else if ((mode & S_IFMT) == S_IFLNK) result[0] = 'l';
  if (mode & S_IRUSR) result[1] = 'r';
  if (mode & S_IWUSR) result[2] = 'w';
  if (mode & S_IXUSR) result[3] = 'x';
  if (mode & S_IRGRP) result[4] = 'r';
  if (mode & S_IWGRP) result[5] = 'w';
  if (mode & S_IXGRP) result[6] = 'x';
  if (mode & S_IROTH) result[7] = 'r';
  if (mode & S_IWOTH) result[8] = 'w';
  if (mode & S_IXOTH) result[9] = 'x';
}

// Display a directory entry as per ls -l
// Assuming we can append to the end of dirname without harm
void display_entry(char* filename, char* dirname) {
    struct stat info;
    char mode_info[] = "----------";

    strcat(dirname, "/");
    strcat(dirname, filename);
    stat(dirname, &info); // info 에 dirname
    
    decode_mode(info.st_mode, mode_info);
    printf("%s %3d", mode_info, (int)info.st_nlink);
    printf(" %6s", getpwuid(info.st_uid)->pw_name);   	// user id     
    printf(" %6s", getgrgid(info.st_gid)->gr_name);   	// group id    
    printf(" %6d", (int)info.st_size);  		// file size   
    printf(" %.12s", 4+ctime(&info.st_mtime));   	// modified
    // Note: not handling symbolic link names
    printf(" %s\n", filename);                		// filename    
}

void showDir(char* dirname, int flags) {
    DIR *dirp; // Will point to the directory object

    if ( (dirp = opendir(dirname)) == NULL ) {
        perror("Failed to open directory");
        exit(1);
    }

    struct dirent *direntp;
    // Remember the where the end of the directory name is
    // This is so we can allow it to added to in display_entry
    // avoiding having to copy it into a new buffer
    int dirnamelen = strlen(dirname); 
    while ( (direntp = readdir(dirp)) != NULL ) {
        if (flags & LFLAG) {
            display_entry(direntp->d_name, dirname);
            dirname[dirnamelen] = '\0';
        }
        else puts(direntp->d_name);
    }

    closedir(dirp);
}
