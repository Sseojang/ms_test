/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:02:13 by seojang           #+#    #+#             */
/*   Updated: 2024/10/18 01:56:06 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	handler(int sig)
{
	if (sig != SIGINT)
		return ;
	write(1, "minishell>^C\n", 13);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(int ac, char **av, char **envp)
{
	char	*line;
	char	*temp;

	line = NULL;
	(void)ac;
	(void)av;
	signal(SIGINT,handler);
	while (1)
	{
		line = readline("minishell>");
		if (!ft_strlen(line))
			continue ;
		if (line)
		{
			ft_tokenizer(line, envp);
			free(line);
			line = NULL;
		}
	}
	return (0);
}