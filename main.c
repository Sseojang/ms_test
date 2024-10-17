/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:02:13 by seojang           #+#    #+#             */
/*   Updated: 2024/10/17 17:59:53 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

// void	handler()
// {
// 	exit(0);
// }

int main(int ac, char **av, char **envp)
{
	char	*line;
	char	*temp;

	line = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell>");
		add_history(line);
		// if (!line)
		// 	break ;

		if (line)
		{
			ft_tokenizer(line, envp);
			free(line);
			line = NULL;
		}
	}
	return (0);
}