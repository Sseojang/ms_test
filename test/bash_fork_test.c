#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void    error(char *msg, int status)
{
    perror(msg);
    exit(status);
}

void    execute_cmd(char *cmd, char **envp)
{
    char *argv[] = {"/bin/sh", "-c", cmd, NULL};
    execve("/bin/sh", argv, envp);
    error("execve failed", 1);
}

void    ft_fork_pipe(char **cmd_arr, char **envp)
{
    int     num_cmds = 0;
    int     pipefd[2];
    int     prev_pipe = -1;
    pid_t   pid;

    while (cmd_arr[num_cmds])
        num_cmds++;  // 명령어 개수 계산

    for (int i = 0; i < num_cmds; i++)
    {
        if (i < num_cmds - 1)
            if (pipe(pipefd) == -1)
                error("pipe error", 1);

        pid = fork();
        if (pid < 0)
            error("fork error", 1);
        else if (pid == 0)  // 자식 프로세스
        {
            if (prev_pipe != -1)  // 이전 파이프가 있으면 표준 입력으로 연결
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }
            if (i < num_cmds - 1)  // 마지막 명령어가 아니면, 출력 파이프로 연결
            {
                close(pipefd[0]);  // 읽기 끝 닫기
                dup2(pipefd[1], STDOUT_FILENO);  // 쓰기 끝을 표준 출력으로 설정
                close(pipefd[1]);
            }
            execute_cmd(cmd_arr[i], envp);  // 명령어 실행
        }
        else  // 부모 프로세스
        {
            if (prev_pipe != -1)  // 이전 파이프 닫기
                close(prev_pipe);
            if (i < num_cmds - 1)
                close(pipefd[1]);  // 쓰기 끝 닫기, 읽기 끝은 다음 명령어에 전달
            prev_pipe = pipefd[0];  // 다음 명령어를 위해 파이프 읽기 끝 저장
        }
    }

    for (int i = 0; i < num_cmds; i++)  // 모든 자식 프로세스 대기
        wait(NULL);
}

int main(int argc, char **argv, char **envp)
{
    if (argc > 1)
        ft_fork_pipe(&argv[1], envp);
    return 0;
}
