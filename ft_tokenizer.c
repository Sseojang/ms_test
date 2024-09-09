/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:25:52 by seojang           #+#    #+#             */
/*   Updated: 2024/09/09 20:13:26 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

	// 파이프로 스플릿 하는데 쿼트는 스킵 하면서 나누기
	// 파이프로 스플릿 후 파싱
	
	// pipex_bonus + 리다이렉션

char	*ft_redirection_check(char *line, int *i)
{
	char	*ptr;

	ptr = NULL;
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		ptr = ft_strdup("2");
		(*i)++;
	}
	else
		ptr = ft_strdup("1");
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		ptr = ft_strdup("4");
		(*i)++;
	}
	else
		ptr = ft_strdup("3");
	return (ptr);
}

char	*ft_single_qoute_check(char *line, int *i)
{
	(*i)++;
	int		first_num;
	char	*ptr;

	ptr = NULL;
	first_num = *i;
	while (line[*i])
	{
		if (line[*i] == 39)
		{
			ptr = ft_substr(line, first_num, *i);
			break ;
		}
		(*i)++;
	}
	return (ptr);
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
			break ;
		}
		(*i)++;
	}
	return (ret);
}

char	*ft_double_qoute_check(char *line, int *i, char **envp)
{
	(*i)++;
	int		first_num;
	char	*temp;
	char	*ptr;

	ptr = NULL;
	first_num = *i;
	while (line[*i])
	{
		if (line[*i] == 34)
		{
			ptr = temp;
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
		(*i)++;
	}
	return (ptr);
}

char	*ft_alpha_digit(char *line, int *i)
{
	char	*temp;
	char	*ptr;

	ptr = NULL;
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
	ptr = temp;
	free(temp);
	return (ptr);
}

void	ft_in_pipe(char *line, char **envp, t_tokken_list **tokken)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			ft_lstadd_back(tokken, ft_lstnew(ft_redirection_check(line, &i)));
		else if (line[i] == 39) // single_qoute
			ft_lstadd_back(tokken, ft_lstnew(ft_single_qoute_check(line, &i)));
		else if (line[i] == 34) // bouble_qoute
			ft_lstadd_back(tokken, ft_lstnew(ft_double_qoute_check(line, &i, envp)));
		else if (line[i] == '$')
			ft_lstadd_back(tokken, ft_lstnew(ft_export_ptr(line, &i, envp)));
		else if (line[i] == '|')
			ft_lstadd_back(tokken, ft_lstnew(ft_strdup("|")));
		else if (ft_is_alpha(line[i]) || ft_is_digit(line[i]))
			ft_lstadd_back(tokken, ft_lstnew(ft_alpha_digit(line, &i)));
		i++; // 스페이스 & 탭
	}
}

void	ft_tokenizer(char *line, char **envp)
{
	t_flag	flag;
	t_tokken_list	*tokken;

	tokken = NULL;
	ft_qoute_check(line, envp, &flag);
	write(1, "\n", 1);
	ft_in_pipe(line, envp, &tokken);

	int	i = 0;
	while (tokken)
	{
		printf("ptr[%d] = %s\n", i, tokken->content);
		tokken = tokken->next;
	}
}