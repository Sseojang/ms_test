void ft_paser_manager(t_tokken_list *tokken, char **envp)
{
    pid_t pid;
    t_val val;
    int pipefd[2];
    int prev_pipe = -1;
    int is_last_command;

    while (tokken)
    {
        ft_val_set(tokken, &val);
        
        is_last_command = !ft_next_pipe(&tokken);

        if (!is_last_command && pipe(pipefd) == -1)
            error("pipe failed", 1);

        ft_find_redir(&tokken, &val);
        ft_find_cmd(tokken, &val);

        pid = fork();
        if (pid < 0)
        {
            error("Fork error", 1);
        }
        else if (pid == 0)
        {
            // Child process
            if (prev_pipe != -1)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }
            if (!is_last_command)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            
            if (!is_last_command)
                close(pipefd[0]);

            if (val.fd_in != -1)
            {
                dup2(val.fd_in, STDIN_FILENO);
                close(val.fd_in);
            }
            if (val.fd_out != -1)
            {
                dup2(val.fd_out, STDOUT_FILENO);
                close(val.fd_out);
            }

            execute_cmd(val.cmd, envp);
            exit(EXIT_FAILURE);  // In case execute_cmd fails
        }
        else
        {
            // Parent process
            if (prev_pipe != -1)
                close(prev_pipe);
            
            if (!is_last_command)
            {
                prev_pipe = pipefd[0];
                close(pipefd[1]);
            }
            else
            {
                prev_pipe = -1;
            }

            // Move to the next command
            while (tokken && tokken->content && ft_strncmp(tokken->content, "|", 1) != 0)
                tokken = tokken->next;
            if (tokken && tokken->content && ft_strncmp(tokken->content, "|", 1) == 0)
                tokken = tokken->next;
        }
    }

    // Close the last pipe and wait for all children
    if (prev_pipe != -1)
        close(prev_pipe);
    while (wait(NULL) > 0);
}