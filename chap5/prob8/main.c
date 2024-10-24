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
    printf("File read success\n");
    printf("Total Line : %d\n", totalLines);
    printf("You can choose 1 ~ %d Line\n", totalLines);
    
    char input[100];
    printf("Pls 'Enter' the line to select : ");
    fgets(input, sizeof(input), stdin);
    
    input[strcspn(input, "\n")] = 0;
    
    printLines(input);
    
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

void printLines(const char *input) {
    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < totalLines; i++) {
            printf("%s\n", savedText[i]);
        }
    } else if (strchr(input, ',') != NULL) {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int line = atoi(token) - 1;
            if (line >= 0 && line < totalLines) {
                printf("%s\n", savedText[line]);
            }
            token = strtok(NULL, ",");
        }
    } else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        start--;
        end--; 
        if (start >= 0 && end < totalLines && start <= end) {
            for (int i = start; i <= end; i++) {
                printf("%s\n", savedText[i]);
            }
        }
    } else {
        int line = atoi(input) - 1;
        if (line >= 0 && line < totalLines) {
            printf("%s\n", savedText[line]);
        }
    }
}

