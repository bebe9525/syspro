#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(int argc, char* argv[]) {
    char str[1024] = "";
    char *command1, *command2;
    int fd[2];

    if (argc > 1) {
        for(int i=1; i<argc; i++) {
            strcat(str, argv[i]);
            strcat(str, " ");
        }
        if(str[strlen(str)-1] == ' ') {
            str[strlen(str)-1] = '\0';
        }
    } else {
        printf("[shell]");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0'; 
    }

    if (strchr(str, '|') != NULL) {
        command1 = strtok(str, "| ");
        command2 = strtok(NULL, "| ");

        if (pipe(fd) == -1) {
            perror("pipe");
            exit(1);
        }

        if (fork() == 0) {
            close(fd[READ]); 
            dup2(fd[WRITE], STDOUT_FILENO);
            close(fd[WRITE]);
            execlp(command1, command1, NULL); 
            perror("execlp");
            exit(1);
        }

        if (fork() == 0) {
            close(fd[WRITE]); 
            dup2(fd[READ], STDIN_FILENO); 
            close(fd[READ]); 
            execlp(command2, command2, NULL); 
            perror("execlp");
            exit(1);
        }

        close(fd[READ]); 
        close(fd[WRITE]);

        wait(NULL); 
        wait(NULL); 
    } else {
        if (fork() == 0) {
            execlp(str, str, NULL);  
            perror("execlp");
            exit(1);
        }
        wait(NULL);  
    }
    return 0; 
}

