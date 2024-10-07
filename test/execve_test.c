#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    char *newargv[] = { "/bin/ls", "-l", "/tmp", NULL };  // 실행할 프로그램과 인자들
    char *newenvp[] = { "PATH=/bin:/usr/bin", NULL };     // 환경 변수

    printf("Before execve\n");

    // execve를 사용하여 /bin/ls 프로그램을 실행
    if (execve("/bin/ls", newargv, newenvp) == -1)
    {
        perror("execve");  // execve 호출에 실패하면 에러 메시지 출력
        exit(EXIT_FAILURE);
    }

    // execve 이후의 코드는 호출되지 않음
    printf("This will not be printed.\n");

    return 0;
}
