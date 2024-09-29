/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:13:37 by seojang           #+#    #+#             */
/*   Updated: 2024/09/29 20:49:52 by seojang          ###   ########.fr       */
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

void	change_standard_input(void)
{
	int	fd = open("test_txt.txt", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	main(int ac, char **av, char **envp)
{
	char	*path;
	char	**argument;

	argument = (char **)malloc(sizeof(char *) * 1);
	argument[0] = strdup("cat");
	path = strdup("/usr/bin/cat");
	//change_standard_input();
	execve(path, argument, envp);
	perror("ERROR");
	exit(EXIT_FAILURE);
}
