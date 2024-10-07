/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:08:50 by seojang           #+#    #+#             */
/*   Updated: 2024/10/07 19:58:50 by seojang          ###   ########.fr       */
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


char	*find_path(t_tokken_list *tokken, const char *env)
{
	char	**paths;
	char	*path;
	int		i;

	paths = ft_split(env, ':');
	i = 0;
	if (access(tokken->content, F_OK | X_OK) == 0)
		return (tokken->content);
	
	while (paths[i])
	{
		path = ft_strjoin(paths[i], tokken->content);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_path(paths);
			return (path);
		}
		i++;
		free(path);
	}
	free_path(paths);
	return (path);
}

void	ft_val_set(t_tokken_list *tokken, t_val *val, int *i)
{
	val->fd_in = -1;
	val->fd_out = -1;
	val->prev_pipe = -1;
	val->heredoc_fd = -1;
	*i = 0;
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

void	execute_cmd(t_tokken_list *tokken, char **envp)
{
	char *const	env[] = {store_path(envp), NULL};
	char *argv[] = {find_path(tokken, env[0]), tokken->next->content, NULL};

	execve(find_path(tokken, env[0]), argv, env);
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
				free(buf);
				break ;
			}
			buf = ft_strjoin(buf, " ");
			write(pipefd[1], buf, ft_strlen(buf));
			free(buf);
		}
		close(pipefd[1]);
	}
}

void	ft_paser_manager(t_tokken_list *tokken, char **envp)
{
	int	pipefd[2];
	t_val	val;
	pid_t	pid;
	int	i;

	ft_val_set(tokken, &val, &i);
	while (tokken)
	{
		ft_redir(tokken, &val);
		pid = fork();
		if (pid < 0)
			error("fork error", 1);
		else if (pid == 0)
		{
			if (val.fd_in != -1)
			{
				dup2(val.fd_in, STDIN_FILENO);
				close(val.fd_in);
			}
			else if (val.prev_pipe != -1)
			{
				dup2(val.prev_pipe, STDIN_FILENO);
				close(val.prev_pipe);
			}
			if (val.fd_out != -1)
			{
				dup2(val.fd_out, STDOUT_FILENO);
				close(val.fd_out);
			}
			else if (tokken->next != NULL)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (val.heredoc_fd != -1)
			{
				dup2(val.heredoc_fd, STDIN_FILENO);
				close(val.heredoc_fd);
			}
			execute_cmd(tokken, envp);
		}
		else
		{
			if (val.prev_pipe != -1)
				close(val.prev_pipe);
			if (tokken->next != NULL)
				close(pipefd[1]);
			val.prev_pipe = pipefd[0];
		}
		tokken = tokken->next;
	}
	while(i < val.tokken_len)
	{
		wait(NULL);
		i++;
	}
}
