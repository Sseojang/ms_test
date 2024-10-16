void    ft_paser_manager(t_tokken_list *tokken, char **envp)
{
    pid_t pid;
    t_val val;
    int pipefd[2];
    int status;
    int last_pid = -1;

    if (pipe(pipefd) == -1)
        error("pipe failed", 1);
    while (tokken)
    {
        ft_paser_func(&tokken, &val, pipefd);
        pid = fork();
        if (pid < 0)
            error("Fork error", 1);
        else if (pid == 0)
            ft_dup(&val, envp, pipefd);
        else
        {
            if (ft_next_pipe(&tokken))
            {
                close(pipefd[1]);
                if (dup2(pipefd[0], STDIN_FILENO) == -1)
                    error("pipe dup2 error", 2);
                close(pipefd[0]);
            }
            else
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }
            last_pid = pid;  // 마지막 자식 프로세스의 PID를 저장
        }
        tokken = tokken->next;
    }
    
    // 마지막 자식 프로세스가 종료될 때까지 기다림
    if (last_pid != -1)
        waitpid(last_pid, &status, 0);
    
    // 나머지 자식 프로세스들이 종료되었는지 확인
    while (wait(NULL) > 0);
}