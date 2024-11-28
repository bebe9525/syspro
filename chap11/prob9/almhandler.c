#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct sigaction newact;
struct sigaction oldact;
void alarmHandler();

int main() {
	newact.sa_handler = alarmHandler;
	oldact.sa_handler = NULL;
	sigfillset(&newact.sa_mask);

	sigaction(SIGALRM, &newact, &oldact);
	alarm(5);
	short i = 0;
	while (1) {
		sleep(1);
		i++;
		printf("%d second\n", i);
	}
	printf("end\n");
}

void alarmHandler(int signo) {
	printf("Wake up\n");
	exit(0);
}
