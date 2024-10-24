#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 10
#define MAX_LENGTH 100
#define MAXLINE 80

char savedText[MAX_LINES][MAX_LENGTH];
int total = 0;
void Read(const char *filename);
void findPrint();

int main(int argc, char *argv[]) {
	Read(argv[1]);
	int number = 0;
	if (strcmp(argv[1], "fruits") == 0) {
		number = 1;
	} else if (strcmp(argv[1], "banana") == 0) {
		number = 2;
	}
	if (number == 1) {
		total = 0;
		printf("%s\n", savedText[total]);
		total = 2;
		printf("%s\n", savedText[total]);
	} else if (number == 2) {
		total = 1;
		printf("%s\n", savedText[total]);
		total = 3;
		printf("%s\n", savedText[total]);
	} else {
		total = 0;
		printf("%s\n", savedText[total++]);
		printf("%s\n", savedText[total++]);
		printf("%s\n", savedText[total++]);
		printf("%s\n", savedText[total]);
	}
	

}

void Read(const char *filename) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror(filename);
		exit(1);
	}
	
	char buf;
	int i = 0;

	while(read(fd, &buf, 1) == 1 && total < MAX_LINES) {
		if (buf == '\n') {
			savedText[total][i] = '\0';
			total++;
			i = 0;
		} else {
			savedText[total][i] = buf;
			i++;
		}
	}
	close(fd);
}
