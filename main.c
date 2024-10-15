/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:02:13 by seojang           #+#    #+#             */
/*   Updated: 2024/10/15 20:08:56 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

// void	handler()
// {
// 	exit(0);
// }
// echo $SHELL$
// 01234567891011
// first_num = 6 - >S
// 11 - 6 = 5
// 10 - 6 + 2 = 
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
		if (line)
			ft_tokenizer(line, envp);
		add_history(line);
		free(line);
		line = NULL;
	}
	return (0);
}