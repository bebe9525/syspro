#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 80

int main(int argc, char *argv[]) {
	FILE *fp;
	int c;
	int line = 0;
	char buffer[MAXLINE];
	int start = 1;
	int number = 0;
    
	if (argc < 2) {
		fprintf(stderr, "file : %s\n", argv[0]);
		return 1;
	}
	if (strcmp(argv[1], "-n") == 0) {
		number = 1;
		start = 2;
	}

	for (int i = start; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			return 2;
		}

		if (number) {
			while (fgets(buffer, MAXLINE, fp) != NULL) {
				line++;
					printf("%3d %s", line, buffer);
			}
		}  else {
			while ((c = getc(fp)) != EOF) {
				putc(c, stdout);
			}
		}
	}

	fclose(fp);
	return 0;
}

