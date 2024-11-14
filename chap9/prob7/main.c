#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	printf("Pls input cmd : ");
	char input;
	scanf("%s", &input); 
	if (argc > 1 && strcmp(argv[1], "ls") == 0) {
		if (argc > 2 && strcmp(argv[2], "-al") == 0) {
			if (fork() == 0) {
				execl("/bin/ls", "ls", "-l", NULL);
				fprintf(stderr, "error");
				exit(1);
			}
			printf("SUCCESS\n\n");
		}
	}

	printf("Pls input cmd : ");
	int child, pid, status;
	pid = fork();
	if (pid == 0) {
		execvp(argv[1], &argv[1]);
		fprintf(stderr, "%s:Unable to execute\n", argv[1]);
	} else {
		child = wait(&status);
		printf("[%d] child process %d end \n", getpid(), pid);
		printf("\tend code %d \n", status>>8);
	}
	printf("SUCCESS\n\n");

	int pid1;
	printf("[%d] Parent process start\n", getpid());
	printf("Parent process end\n");
	printf("Exit\n");
}
