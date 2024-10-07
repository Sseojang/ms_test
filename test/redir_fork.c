#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

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

void    handle_redirection(char *token, int *fd_in, int *fd_out, int *heredoc_fd)
{
    if (strstr(token, ">>")) // Append output to file
    {
        char *file = strtok(token, ">>");
        *fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (*fd_out < 0)
            error("append output error", 1);
    }
    else if (strstr(token, ">")) // Output to file
    {
        char *file = strtok(token, ">");
        *fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (*fd_out < 0)
            error("output error", 1);
    }
    else if (strstr(token, "<")) // Input from file
    {
        char *file = strtok(token, "<");
        *fd_in = open(file, O_RDONLY);
        if (*fd_in < 0)
            error("input error", 1);
    }
    else if (strstr(token, "<<")) // Heredoc input
    {
        char *delimiter = strtok(token, "<<");
        char buffer[1024];
        int pipefd[2];
        pipe(pipefd); // Create a pipe to simulate heredoc
        *heredoc_fd = pipefd[0]; // Input side for the heredoc
        
        // Write heredoc contents into pipe
        while (1)
        {
            printf("> ");
            fgets(buffer, 1024, stdin);
            if (strncmp(buffer, delimiter, strlen(delimiter)) == 0)
                break;
            write(pipefd[1], buffer, strlen(buffer));
        }
        close(pipefd[1]);
    }
}

void    ft_fork_pipe(char **cmd_arr, char **envp)
{
    int     num_cmds = 0;
    int     pipefd[2];
    int     prev_pipe = -1;
    int     fd_in = -1, fd_out = -1, heredoc_fd = -1;
    pid_t   pid;

    while (cmd_arr[num_cmds])
        num_cmds++;  // 명령어 개수 계산

    for (int i = 0; i < num_cmds; i++)
    {
        char *cmd = cmd_arr[i];

        // 리다이렉션 및 히어독 처리
        handle_redirection(cmd, &fd_in, &fd_out, &heredoc_fd);

        if (i < num_cmds - 1)
            if (pipe(pipefd) == -1)
                error("pipe error", 1);

        pid = fork();
        if (pid < 0)
            error("fork error", 1);
        else if (pid == 0)  // 자식 프로세스
        {
            if (fd_in != -1)  // 파일에서 입력을 받는 경우
            {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            else if (prev_pipe != -1)  // 이전 파이프가 있으면 표준 입력으로 연결
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            if (fd_out != -1)  // 파일로 출력하는 경우
            {
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }
            else if (i < num_cmds - 1)  // 마지막 명령어가 아니면, 출력 파이프로 연결
            {
                close(pipefd[0]);  // 읽기 끝 닫기
                dup2(pipefd[1], STDOUT_FILENO);  // 쓰기 끝을 표준 출력으로 설정
                close(pipefd[1]);
            }

            if (heredoc_fd != -1)  // 히어독에서 입력 받는 경우
            {
                dup2(heredoc_fd, STDIN_FILENO);
                close(heredoc_fd);
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
