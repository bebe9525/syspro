#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[]) {
	int fd;

	if ((fd = open(argv[1], O_RDWR)) == -1)
		printf("파일 열기 오�\n�");
	else printf("파밍명 :  %s 파일 디스크립터 : %d\n", argv[1], fd);

	close(fd);
	exit(0);
}
