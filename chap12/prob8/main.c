#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAXLINE 100

int main(int argc, char* argv[]) {
    int pid1, pid2, fd[2];
    char line[MAXLINE];

    printf("parent process start\n");

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) { 
        close(fd[0]); 

        printf("input string: ");
        fgets(line, sizeof(line), stdin);
        line[strlen(line) - 1] = '\0'; 

        write(fd[1], line, strlen(line) + 1);
        close(fd[1]);  

        exit(0); 
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) { 
        close(fd[1]); 

        read(fd[0], line, MAXLINE);
        close(fd[0]); 

        for (int i = 0; line[i]; i++) {
            line[i] = toupper((unsigned char) line[i]);
        }

        printf("%s\n", line);
        exit(0);  
    }

    wait(NULL); 
    wait(NULL); 

    return 0;
}

