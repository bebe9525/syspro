#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 10
#define MAX_LENGTH 100

char savedText[MAX_LINES][MAX_LENGTH];
int totalLines = 0;

void Read(const char *filename);
void printReversed();

int main(int argc, char *argv[]) {
    Read(argv[1]);

	printReversed();
    
    return 0;
}

void Read(const char *filename) {
    int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror(filename);
		exit(1);
	}

    char buf;
    int i = 0;

    while(read(fd, &buf, 1) == 1 && totalLines < MAX_LINES) {
        if (buf == '\n') {
            savedText[totalLines][i] = '\0';
            totalLines++;
            i = 0;
        } else {
            savedText[totalLines][i] = buf;
            i++;
        }
    }
    close(fd);
}

void printReversed() {
    for (int i = totalLines - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }
}
