#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 100

int main(int argc, char* argv[])
{
    int n, pid, fd[2];
    char line[MAXLINE];

    pipe(fd); 

    if ((pid = fork()) == 0) {  
        close(fd[0]);           
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);            
        printf("Send: [%d] Hello from PID %d\n", getpid(), getpid());
        exit(0);
    } else {                     
        close(fd[1]);         
        while ((n = read(fd[0], line, MAXLINE)) > 0)
            write(STDOUT_FILENO, line, n);
        printf("Recv: [%d] Hello from PID %d\n", getpid(), pid);
    }

    exit(0);
}

