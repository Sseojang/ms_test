/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrtie_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:46:51 by seojang           #+#    #+#             */
/*   Updated: 2024/09/29 02:14:01 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av, char **envp)
{
	char	*line;
	char	**lines;

	line = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		line = readline(">");
		write(0, &lines, ft_strlen(line));
		free(line);
	}
	int	i = 0;
	while (lines[i] != '\0')
	return (0);
}