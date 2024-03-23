/*
  testOpen.c
  John Sterling

  opens testOpen.txt for writing
  By default writes the contents of BUF
  Otherwise the first command line argument (could be ion quotes)

  Closes testOpen.txt and reopens it for reading. Reads the file and
  write to standard output
 */

#include <fcntl.h>   // open, O_WRONLY, O_CREAT
#include <sys/stat.h> // S_IRWXU, S_IRWXG, S_IRWXO
#include <stdio.h>   // perror, fprintf, stderr
#include <stdlib.h>  // exit
#include <unistd.h>  // close, write
#include <string.h>  // strlen

const char* const BUF = "Default junk to write\n";

// If you prefer named constants to 0666
const mode_t CREATE_MODE = S_IRWXU | S_IRWXG | S_IRWXO;

int main(int argc, char *argv[]) {
    //    int fd = open("testOpen.txt", O_WRONLY | O_CREAT, 0666);
    int fd = open("testOpen.txt", O_WRONLY | O_CREAT, CREATE_MODE);
    if (fd == -1) {
        perror("Failed to create testOpen.txt");
        exit(1);
    }
    if (argc > 1) {
        if (write(fd, argv[1], strlen(argv[1])) < 0) {
            perror("Failed to write to testOpen.txt");
            exit(1);
        }
    } else if (write(fd, BUF, strlen(BUF)) < 0) {
            perror("Failedd to write to testOpen.txt");
            exit(1);
    }
    fprintf(stdout, "Finished writing testOpen.txt\n");
    
    if (close(fd) < 0) {
        perror("Couldn't close testOpen.txt Wierd!");
        exit(1);
    }

    // Open for reading
    fd = open("testOpen.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open testOpen.txt for reading");
        exit(1);
    }
    char readBuf[80];
    int bytesRead = 0;
    while ( (bytesRead = read(fd, readBuf, 80)) > 0 ) {
	write(1, readBuf, bytesRead);
	//write(STDOUT_FILENO, readBuf, bytesRead);
    }
    //return 0; // Using C99, this is not needed
}
