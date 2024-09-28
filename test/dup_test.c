/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:13:37 by seojang           #+#    #+#             */
/*   Updated: 2024/09/29 02:13:59 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#define BUFFER_SIZE 42

int	main()
{
	char	*buf = "HELLO WORLD!\n";
	int		*file_fd = open("./test", O_WRONLY);

	int		new_stdout = dup(STDOUT_FILENO);
	dup2(file_fd, STDOUT_FILENO);

	write(new_stdout, buf, BUFFER_SIZE);
}
