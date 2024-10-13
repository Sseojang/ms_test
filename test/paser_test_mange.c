// Original function with comments indicating potential issues
void ft_paser_manager(t_tokken_list *tokken, char **envp)
{
    pid_t pid;
    t_val val;
    int pipefd[2] = {-1, -1};
    t_tokken_list *lst;

    ft_val_set(tokken, &val);
    while (tokken)
    {
        if (tokken->next && tokken->next->content && ft_strncmp(tokken->next->content, "|", 1) == 0)
        {
            if (pipe(pipefd) == -1)
                error("pipe error", 1);
            val.fd_out = pipefd[1];
            tokken = tokken->next;
        }
        else
            val.fd_out = -1;
        
        lst = tokken;
        // ISSUE 1: Potential infinite loop if lst->content is NULL
        while (lst->content != NULL || ft_strncmp(lst->content, "|", 1) != 0)
        {
            if (ft_strncmp(lst->content, ">", 1) == 0)
            {
                ft_redir_out(&lst, &val);
                break;
            }
            else if (ft_strncmp(lst->content, ">>", 2) == 0)
            {
                ft_redir_out(&lst, &val); // ISSUE 2: Should be ft_redir_add
                break;
            }
            else if (ft_strncmp(lst->content, "<", 1) == 0)
            {
                ft_redir_out(&lst, &val); // ISSUE 3: Should be ft_redir_open
                break;
            }
            lst = lst->next;
        }

        pid = fork();
        if (pid < 0)
            error("Fork error", 1);
        else if (pid == 0)
        {
            // Child process
            if (val.fd_in != -1)
            {
                if (dup2(val.fd_in, STDIN_FILENO) == -1)
                    error("dup2 failed", 1);
                close(val.fd_in);
            }
            if (val.fd_out != -1)
            {
                if (dup2(val.fd_out, STDOUT_FILENO) == -1)
                    error("dup2 failed", 2);
                close(val.fd_out);
            }
            execute_cmd(&tokken, envp);
            exit(1);
        }
        else
        {
            // Parent process
            if (val.fd_in != -1)
                close(val.fd_in);
            if (val.fd_out != -1)
                close(val.fd_out);
            val.fd_in = pipefd[0];
            pipefd[0] = -1;
            pipefd[1] = -1;
        }
        tokken = tokken->next;
    }
    if (val.fd_in != -1)
        close(val.fd_in);
    while (wait(NULL) > 0);
}