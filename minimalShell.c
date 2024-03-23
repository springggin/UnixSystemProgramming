/*
  minimalShell
  "Looping":
     Displays a prompt
     Takes in a command
     Executes the command
  Since it execs without forking, it can only run a single command.
  Also doesn't tokenize the input...
 */

#include <stdio.h>   // printf, fgets
#include <string.h>  // strlen
#include <unistd.h>  // execlp
#include <stdbool.h> // true

int main() 
{
    while(true) {
        printf(":-) ");
        char command[80];
        fgets(command, 80, stdin);
        int len = strlen(command);
        if (command[len-1] == '\n') command[len-1] = '\0';
        execlp(command, command, NULL);
        perror("Failed to exec");
    }
}
