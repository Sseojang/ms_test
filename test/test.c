void ft_paser_manager(t_tokken_list *tokken, char **envp)
{
    pid_t pid;
    t_val val;
    int pipefd[2];

    while (tokken)
    {
        if (pipe(pipefd) == -1)
        {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }

        ft_val_set(tokken, &val);
        
        pid = fork();
        if (pid < 0)
        {
            error("Fork error", 1);
        }
        else if (pid == 0)  // 자식 프로세스
        {
            // 리다이렉션 처리
            if (val.fd_in != -1)
                dup2(val.fd_in, STDIN_FILENO);  // 입력 리다이렉션
            if (val.fd_out != -1)
                dup2(val.fd_out, STDOUT_FILENO); // 출력 리다이렉션

            // 파이프가 존재하면 stdout을 파이프에 연결할 필요 없음
            if (ft_pipe_check(tokken))
            {
                // 여기서는 파이프에 연결하는 대신,
                // 이미 리다이렉션된 stdout을 사용할 수 있음
            }

            execute_cmd(&tokken, envp); // 명령 실행
            exit(0); // 자식 프로세스 종료
        }
        else  // 부모 프로세스
        {
            close(pipefd[1]); // 쓰기 끝 닫기

            if (ft_pipe_check(tokken))
            {
                // 다음 명령어가 있으면, pipefd[0]를 다음 명령어의 STDIN으로 사용할 수 있음
                val.prev_pipe = pipefd[0];
            }
            else
            {
                close(pipefd[0]); // 더 이상 필요하지 않으면 읽기 끝 닫기
            }
        }

        tokken = tokken->next; // 다음 토큰으로 이동
    }

    while (wait(NULL) > 0); // 모든 자식 프로세스가 종료될 때까지 대기
}
