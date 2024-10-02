#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAX 5

char line[MAXLINE]; // 입력 줄
char longest[MAXLINE]; // 가장 긴 줄
/* 입력 줄 가운데 가장 긴 줄을 프린트한다. */
char lines[MAX][MAXLINE];

int main(){
	int len;
	int max;
	max = 0;
	int i, j;

	int count;
	count = 0;

	while(count < MAX && gets(line) != NULL) {
		len = strlen(line);

		if(count < MAX) {
            copy(line, lines[count]);
			count++;
		}
	}

	for (i = 0; i < MAX - 1; i++) {
		for (j = i + 1; j < MAX; j++) {
			if (strlen(lines[i]) < strlen(lines[j])) {
				char temp[MAXLINE];
				copy(lines[i], temp);
				copy(lines[j], lines[i]);
				copy(temp, lines[j]);
			}
		}
	}
	for (i = 0; i < MAX; i++) {
		printf("%s\n", lines[i]);
	}

	return 0;
	}

