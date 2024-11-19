#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXARG 100

// 입력을 공백, 탭, 개행으로 분리하는 함수
void parse_input(char *input, char *args[]) {
    char *token;
    int i = 0;

    token = strtok(input, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;  
}

int main() {
    char input[256];
    char *args[MAXARG];
    pid_t pid;

    while (1) {
        printf("Pls input cmd : ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Input error");
            continue;
        }

        // 개행 문자 제거
        input[strcspn(input, "\n")] = 0;

        // 백그라운드 실행 여부 확인
        int is_background = 0;
        if (strlen(input) > 0 && input[strlen(input) - 1] == '&') {
            is_background = 1;
            input[strlen(input) - 1] = 0;  // & 제거
        }

        parse_input(input, args);

        // 유효한 명령어인지 확인
        if (
            (strcmp(args[0], "ls") == 0 && args[1] != NULL && strcmp(args[1], "-al") == 0) ||
            (strcmp(args[0], "wc") == 0 && args[1] != NULL)
           ) {

            pid = fork();
            if (pid == -1) {
                perror("fork failed");
                exit(1);
            }

            if (pid == 0) { // 자식 프로세스
                printf("[%d] child process start\n", getpid());
                execvp(args[0], args);
                perror("exec failed"); // exec 실패 시 메시지 출력
                exit(1);
            } else { // 부모 프로세스
                printf("[%d] Parent process start\n", getpid());

                if (!is_background) {
                    waitpid(pid, NULL, 0);
                    printf("[%d] Parent process end\n", getpid());
                    printf("SUCCESS\n\n");
                } else {
                    printf("[%d] child process end %d\n", getpid(), pid);
                    printf("SUCCESS\n\n");

                    int status;
                    pid_t finished_pid = waitpid(pid, &status, 0);
                    if (finished_pid == pid) {
                        if (WIFEXITED(status)) {
                            printf("[%d] child process end %d\n", getpid(), finished_pid);
                        } else {
                            printf("Child process terminated abnormally\n");
                        }
                    }
                }
            }
        } else {
            // 유효하지 않은 명령어 처리
            printf("[%d] Parent process start\n", getpid());
            printf("[%d] Parent process end\n", getpid());
            printf("Exit\n");
            break;  // 루프 종료
        }
    }

    return 0;
}

