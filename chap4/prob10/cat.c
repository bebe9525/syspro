#include <stdio.h>
#include <string.h>
#define MAXLINE 80

int main(int argc, char *argv[]) {
	FILE *fp1, *fp2, *fp3;
	int c;
	int line = 0;
	char buffer[MAXLINE];
	
	if (strcmp(argv[1], "-n")) {
		while (fgets(buffer, MAXLINE, fp1) != NULL) {
			line++;
			printf("%3d %s", line, buffer);
		}
	} else {
	fp1 = fopen(argv[1], "r");
	if (fp1 == NULL) {
		return 2;
	} else {
		c = getc(fp1);
 	    while (c != EOF) { 
        putc(c, stdout);
        c = getc(fp1);
        }
	}
	fp2 = fopen(argv[2], "r");
	if (fp2 == NULL) {
		return 2;
	} else { 
		c = getc(fp2);
        while (c != EOF) { 
        putc(c, stdout);
		c = getc(fp2);
        }
	}
	fp3 = fopen(argv[3], "r");
	if (fp3 == NULL) {
		return 2;
	} else {
		c = getc(fp3);
        while (c != EOF) {
        putc(c, stdout);
		c = getc(fp3);
        }
	}
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}

