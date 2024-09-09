/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:25:52 by seojang           #+#    #+#             */
/*   Updated: 2024/09/09 18:59:16 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

	// 파이프로 스플릿 하는데 쿼트는 스킵 하면서 나누기
	// 파이프로 스플릿 후 파싱
	
	// pipex_bonus + 리다이렉션

void	ft_redirection_check(char *line, int *i, char **ptr)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		*ptr = ft_strdup("2");
		*i++;
	}
	else
		*ptr = ft_strdup("1");
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*ptr = ft_strdup("4");
		*i++;
	}
	else
		*ptr = ft_strdup("3");
}

void	ft_single_qoute_check(char *line, int *i, char **ptr)
{
	*i++;
	int	first_num;

	first_num = *i;
	while (line[*i])
	{
		if (line[*i] == 39)
		{
			*ptr = ft_substr(line, first_num, *i);
			break ;
		}
		*i++;
	}
}

char	*ft_export_push(char *temp, char **envp)
{
	int	i;
	int	j;
	char	*ret;

	i = 0;
	while (envp[i])
	{
		j = 0;
		if (envp[i][0] == temp[j])
		{
			while (envp[i][j] != '=')
			{
				if (envp[i][j] == temp[j])
					j++;
				else
					break ;
			}
			if (envp[i][j] == '=' && temp[j] == '\0') //변수 있음
			{
				j++;
				while (envp[i][j] != '\0')
					ret = ft_strjoin(ret, ft_strdup(&envp[i][j++]));
				return (ret);
			}
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*ft_export_ptr(char *line, int *i, char **envp)
{
	char	*temp;
	char	*ret;
	int		first_num;

	first_num = ++(*i);
	while (line[*i])
	{
		if (line[*i + 1] == ' ' || line[*i + 1] == '\t' || line[*i + 1] == '"' || line[*i + 1] == '\0')
		{
			temp = ft_substr(line, first_num, *i + 1 - first_num);
			ret = ft_export_push(temp, envp);
			return (ret);
		}
		*i++;
	}
}

void	ft_double_qoute_check(char *line, int *i, char **ptr, char **envp)
{
	*i++;
	int		first_num;
	char	*temp;

	first_num = *i;
	while (line[*i])
	{
		if (line[*i] == 34)
		{
			*ptr = temp;
			free(temp);
			break ;
		}
		else if (line[*i] == '$')
		{
			temp = ft_strjoin(temp, ft_export_ptr(line, i, envp));
		}
		else
		{
			temp = ft_strjoin(temp, ft_strdup(&line[*i]));
		}
		*i++;
	}
}

void	ft_alpha_digit(char *line, int *i, char **ptr)
{
	char	*temp;

	while (line[*i])
	{
		if (ft_is_alpha(line[*i]) || ft_is_digit(line[*i]))
		{
			temp = ft_strjoin(temp, ft_strdup(&line[*i]));
		}
		else
			break ;
		(*i)++;
	}
	--(*i);
	*ptr = temp;
	free(temp);
}

char	**ft_in_pipe(char *line, char **envp)
{
	char	**ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			ft_redirection_check(line, &i, &ptr[j++]);
		else if (line[i] == 39) // single_qoute
			ft_single_qoute_check(line, &i, &ptr[j++]);
		else if (line[i] == 34) // bouble_qoute
			ft_double_qoute_check(line, &i, &ptr[j++], envp);
		else if (line[i] == '$')
			ptr[j++] = ft_export_ptr(line, &i, envp);
		else if (line[i] == '|')
			ptr[j++] = ft_strdup("|");
		else if (ft_is_alpha(line[i]) || ft_is_digit(line[i]))
			ft_alpha_digit(line, &i, &ptr[j++]);
		i++; // 스페이스 & 탭
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**ft_none_pipe(char *line, char **envp)
{
	char	**ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			ft_redirection_check(line, &i, &ptr[j++]);
		else if (line[i] == 39) // single_qoute
			ft_single_qoute_check(line, &i, &ptr[j++]);
		else if (line[i] == 34) // bouble_qoute
			ft_double_qoute_check(line, &i, &ptr[j++], envp);
		else if (line[i] == '$')
			ptr[j++] = ft_export_ptr(line, &i, envp);
		else if (ft_is_alpha(line[i]) || ft_is_digit(line[i]))
			ft_alpha_digit(line, &i, &ptr[j++]);
		i++; // 스페이스 & 탭
	}
	ptr[j] = NULL;
	return (ptr);
}

void	ft_tokenizer(char *line, char **envp)
{
	t_flag	flag;
	char	**ptr;

	ft_qoute_check(line, envp, &flag);
	write(1, "\n", 1);
	if (flag.pipe == 1)
		ptr = ft_in_pipe(line, envp);
	else
		ptr = ft_none_pipe(line, envp);
	int	i = 0;
	while (ptr[i])
	{
		printf("ptr[%d] = %s\n", i, ptr[i]);
	}
}