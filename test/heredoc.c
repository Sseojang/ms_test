/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:24:13 by seojang           #+#    #+#             */
/*   Updated: 2024/09/28 20:40:01 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

//execve 사용법
//브라스 고려

size_t	ft_strlen(const char *s)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		cnt++;
		i++;
	}
	return (cnt);
}

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	size_t		i;
	char		*p;

	len = ft_strlen(s);
	i = 0;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (i < len)
		p[i++] = *s++;
	p[i] = '\0';
	return (p);
}


char	**ft_heredoc(char **av)
{
	char	*line;
	char	**lines;
	int		i;

	line = NULL;
	i = 0;
	if (av[0][0] == '<' && av[0][1] == '<')
	{
		while (1)
		{
			line = readline(">");
			if (ft_strncmp(av[1], line, ft_strlen(av[1])) == 0)
				break ;
			else
			{
				lines[i] = ft_strdup(line);
				line = NULL;
				i++;
			}
		}
		return (lines);
	}
	else // command execv 사용
}

int	main(int ac, char **av)
{
	int	i;
	char	**lines;

	i = 0;
	while (av[i])
	{
		if (ft_strcmp(av[i], "<<", ft_strlen(av[i])) == 0)
		{
			lines = ft_heredoc(av);
			return 0;
		}
		i++;
	}
}