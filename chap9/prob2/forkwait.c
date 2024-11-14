#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int pid, child, status;

	printf("[%d] parental process start \n", getpid());
	pid = fork();
	if (pid == 0) {
		printf("[%d] child Process start \n", getpid());
		exit(1);
	}
	child = wait(&status);
	printf("[%d] Child Process %d end \n", getpid(), child);
	printf("\tend code %d\n", status>>8);
}
