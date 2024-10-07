/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:50:15 by seojang           #+#    #+#             */
/*   Updated: 2024/10/07 16:12:21 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#define BUFFER_SIZE 42

// int main(int ac, char **av, char **envp)
// {
// 	char *line;

// 	line = NULL;
// 	(void)ac;
// 	(void)av;
// 	while (1)
// 	{
// 		line = readline("minishell>");
// 		if (line)
// 			ft_tokenizer(line, envp);
// 		add_history(line);
// 		free(line);
// 	}
// 	return (0);
// }

char	*heredoc(char *eof)
{
	char	*line;
	char	*temp;

	line = NULL;
	while (1)
	{
		temp = readline(">");
		if (!ft_strncmp(eof, line))
			break ;
		line = ft_strjoin(line, ft_strjoin(temp, ft_strdup("\n")));
		free(temp);
	}
	return (line);
}

int	find_heredoc()
{
	
}

int	main()
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(">");
		free(line);
	}
}