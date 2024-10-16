/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:08:50 by seojang           #+#    #+#             */
/*   Updated: 2024/10/16 19:08:57 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_paser_func(t_tokken_list **tokken, t_val *val, int *pipefd)
{
	ft_val_set(*tokken, val);
	ft_find_pipe(*tokken, val, pipefd);
	ft_find_redir(tokken, val);
	ft_find_cmd(*tokken, val);
}

void ft_paser_manager(t_tokken_list *tokken, char **envp)
{
	pid_t pid;
	t_val val;
	int pipefd[2] = {-1, -1};
	int prev_pipe = -1;
	int status;

	while (tokken)
	{
		if (ft_next_pipe(tokken))
		{
			if (pipe(pipefd) == -1)
				error("pipe failed", 1);
		}
		else
		{
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
		ft_paser_func(&tokken, &val, pipefd);
		pid = fork();
		if (pid < 0)
			error("Fork error", 1);
		else if (pid == 0)
		{
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (pipefd[0] != -1)
				close(pipefd[0]);
			if (ft_next_pipe(tokken))
				ft_dup(&val, envp, pipefd);
			else
				ft_dup(&val, envp, NULL);
			exit(1);
		}
		else
		{
			if (prev_pipe != -1)
				close(prev_pipe);
			if (pipefd[1] != -1)
				close(pipefd[1]);
			prev_pipe = pipefd[0];
		}
		while (tokken && tokken->content && ft_strncmp(tokken->content, "|", 1) != 0)
		{
			printf("test here : {%s}\n", tokken->content);
			tokken = tokken->next;
		}
		if (tokken && tokken->content && ft_strncmp(tokken->content, "|", 1) == 0)
			tokken = tokken->next;
	}
	if (prev_pipe != -1)
		close(prev_pipe);
	while (wait(&status) > 0);
}
