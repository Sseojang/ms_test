/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:08:50 by seojang           #+#    #+#             */
/*   Updated: 2024/10/07 19:37:09 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

int	ft_lst_len(t_tokken_list *tokken)
{
	int	ret;

	ret = 0;
	while (tokken)
	{
		ret++;
		tokken = tokken->next;
	}
	return (ret);
}

char	*store_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	return (path);
}

void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	paths = NULL;
}


char *find_path(t_tokken_list *tokken, const char *env)
{
    char **paths;
    char *path;
    char *full_path;
    int i;

    if (!tokken || !tokken->content || !env)
        return NULL;

    if (access(tokken->content, F_OK | X_OK) == 0)
        return ft_strdup(tokken->content);

    paths = ft_split(env, ':');
    if (!paths)
        return NULL;

    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        if (!path)
        {
           // free_path(paths);
            return NULL;
        }
        full_path = ft_strjoin(path, tokken->content);
     //   free(path);
        if (!full_path)
        {
      //      free_path(paths);
            return NULL;
        }
        if (access(full_path, F_OK | X_OK) == 0)
        {
        //    free_path(paths);
            return full_path;
        }
       // free(full_path);
        i++;
    }
   // free_path(paths);
    return NULL;
}

void	ft_val_set(t_tokken_list *tokken, t_val *val)
{
	val->fd_in = -1;
	val->fd_out = -1;
	val->prev_pipe = -1;
	val->heredoc_fd = -1;
	val->tokken_len = ft_lst_len(tokken);
}

void	error(char *s, int num)
{
	if (num == 1)
		write(2, s, ft_strlen(s));
	else if (num == 2)
		perror(s);
	else if (num == 3)
	{
		write(2, "command not found: ", ft_strlen("command not found: "));
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}

void execute_cmd(t_tokken_list *tokken, char **envp)
{
    char *const env[] = {store_path(envp), NULL};
    char **argv = NULL;
    int arg_count = 0;
    t_tokken_list *current = tokken;
    char *path = NULL;

    if (!tokken || !tokken->content || !envp)
        error("Invalid command or environment", 1);

    while (current && current->content && ft_strncmp(current->content, "|", 1) != 0) {
        arg_count++;
        current = current->next;
    }

    argv = malloc(sizeof(char *) * (arg_count + 1));
    if (!argv)
        error("Memory allocation failed", 2);

    current = tokken;
    for (int i = 0; i < arg_count; i++) {
        if (!current || !current->content) {
        //    free(argv);
            error("Unexpected end of command", 1);
        }
        argv[i] = current->content;
        current = current->next;
    }
    argv[arg_count] = NULL;

    path = find_path(tokken, env[0]);
    if (!path) {
    //    free(argv);
        error(tokken->content, 3);  // Command not found
    }

    execve(path, argv, envp);

    // If execve returns, it means it failed
  //  free(path);
    path = NULL;  // Prevent double free
  //  free(argv);
    argv = NULL;  // Prevent double free
    error("execve failed", 1);
}


void	ft_redir(t_tokken_list *tokken, t_val *val)
{
	if (tokken->next == NULL)
		error("syntax error: unexpected end of token", 1);
	if (ft_strncmp(tokken->content, ">>", 2))
	{
		char	*file = tokken->next->content;
		val->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (val->fd_out < 0)
			error("append error", 1);
	}
	else if (ft_strncmp(tokken->content, ">", 1))
	{
		char	*file = tokken->next->content;
		val->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (val->fd_out < 0)
			error("output error", 1);
	}
	else if (ft_strncmp(tokken->content, "<", 1))
	{
		char	*file = tokken->next->content;
		val->fd_in = open(file, O_RDONLY);
		if (val->fd_in < 0)
			error("input error", 1);
	}
	else if (ft_strncmp(tokken->content, "<<", 2))
	{
		char	*eof = tokken->next->content;
		char	*buf;
		int		pipefd[2];
		pipe(pipefd);
		val->heredoc_fd = pipefd[0];
		while (1)
		{
			buf = readline(">");
			if (ft_strncmp(buf, eof, ft_strlen(eof)) == 0)
			{
		//		free(buf);
				break ;
			}
			buf = ft_strjoin(buf, " ");
			write(pipefd[1], buf, ft_strlen(buf));
		//	free(buf);
		}
		close(pipefd[1]);
	}
}

void ft_paser_manager(t_tokken_list *tokken, char **envp)
{
    t_val val;
    int pipe_fd[2] = {-1, -1};
    pid_t pid;

    ft_val_set(tokken, &val);
    while (tokken)
    {
		ft_redir(tokken, &val);
        if (tokken->next && tokken->next->content && ft_strncmp(tokken->next->content, "|", 1) == 0)
        {
            if (pipe(pipe_fd) == -1)
                error("Pipe creation failed", 2);
            val.fd_out = pipe_fd[1];
        }
        else
            val.fd_out = -1;

        pid = fork();
        if (pid < 0)
            error("Fork failed", 2);
        else if (pid == 0)
        {
            if (val.fd_in != -1)
            {
                if (dup2(val.fd_in, STDIN_FILENO) == -1)
                    error("dup2 failed", 2);
                close(val.fd_in);
            }
            if (val.fd_out != -1)
            {
                if (dup2(val.fd_out, STDOUT_FILENO) == -1)
                    error("dup2 failed", 2);
                close(val.fd_out);
            }
            execute_cmd(tokken, envp);
            // Child process should not reach here, but just in case:
            exit(EXIT_FAILURE);
        }
        else
        {
            if (val.fd_in != -1)
                close(val.fd_in);  // 부모 프로세스에서 파이프 읽기 끝을 닫음
            if (val.fd_out != -1)
                close(val.fd_out);  // 부모 프로세스에서 파이프 쓰기 끝을 닫음
            
            val.fd_in = pipe_fd[0];  // 부모 프로세스는 다음 커맨드를 위해 pipe_fd[0]을 읽기용으로 설정
            pipe_fd[0] = -1;
            pipe_fd[1] = -1;
        }

        // 다음 커맨드를 위해 토큰을 이동
        while (tokken && tokken->content && ft_strncmp(tokken->content, "|", 1) != 0)
            tokken = tokken->next;
        if (tokken && tokken->content && ft_strncmp(tokken->content, "|", 1) == 0)
            tokken = tokken->next;
    }

    if (val.fd_in != -1)
        close(val.fd_in);  // 마지막으로 사용한 파이프 읽기 끝 닫기

    while (wait(NULL) > 0);  // 모든 자식 프로세스가 끝날 때까지 기다림
}

