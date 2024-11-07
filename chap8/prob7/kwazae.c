#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
	int number = 0;
	int path = 0;

	if (argc > 1 && strcmp(argv[1], "-e") == 0) {
		number = 1;
		if (argc > 2 && strcmp(argv[2], "PATH") == 0) {
			path = 1;
		}
	} else if (strcmp(argv[1], "-u") == 0) {
		number = 2;
	} else if (strcmp(argv[1], "-g") == 0) {
		number = 3;
	} else if (strcmp(argv[1], "-i") == 0) {
		number = 4;
	} else if (strcmp(argv[1], "-p") == 0) {
		number = 5;
	}

	if (number == 1) {
		if (path == 1) {
			char *ptr;

			ptr = getenv("PATH");
			printf("PATH = %s \n", ptr);

			exit(0);
		} else {
		char **ptr;
		extern char **environ;

		for (ptr = environ; *ptr != 0; ptr++)
			printf("%s \n", *ptr);
		
			exit(0);
		}
	} else if (number == 2) {
		printf("My Realistic User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
		printf("My Valid User ID : %d(%s) \n",geteuid(), getpwuid(geteuid())->pw_name);
	} else if (number == 3) {
		printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
		printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
	} else if (number == 4) {
		printf("My process number : [%d] \n", getpid());
	} else if (number == 5) {
		printf("My parent's process number : [%d] \n", getppid());
	}
}
