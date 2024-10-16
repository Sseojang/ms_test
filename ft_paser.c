/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:08:50 by seojang           #+#    #+#             */
/*   Updated: 2024/10/16 18:19:08 by seojang          ###   ########.fr       */
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

void	ft_paser_manager(t_tokken_list *tokken, char **envp)
{
	pid_t pid;
	t_val val;
	int pipefd[2] = {-1 , -1};
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
				printf("print1 : {%d}\n", pipefd[1]);
				close(pipefd[1]);
				if (dup2(pipefd[0], STDIN_FILENO) == -1)
					error("pipe dup2 error", 2);
				printf("print2 : {%d}\n", pipefd[0]);
				close(pipefd[0]);
			}
			else
			{
				printf("print3 : {%d}\n", pipefd[0]);
				close(pipefd[0]);
				printf("print4 : {%d}\n", pipefd[1]);
				close(pipefd[1]);
			}
			last_pid = pid;
		}
		tokken = tokken->next;
	}
	if (last_pid != -1)
		waitpid(last_pid, &status, 0);
	//while (wait(NULL) > 0);
}
