/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser_arr_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:31:18 by seojang           #+#    #+#             */
/*   Updated: 2024/10/04 20:47:15 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

int	ft_arr_find_pipe(char *tokken_arr)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (tokken_arr)
	{
		if (tokken_arr[0] == '|')
			ret++;
		i++;
	}
	return (ret);
}

int	ft_lst_len(t_tokken_list *tokken)
{
	int	ret;

	ret = 0;
	while (tokken)
	{
		ret++;
		tokken = tokken->next;
	}
	return (ret);
}

char	*ft_lst_to_arr(t_tokken_list *tokken)
{
	char	*ret;
	int	i;

	i = 0;
	ret = malloc(sizeof(char) * (ft_lst_len(tokken) + 1));
	while (tokken)
	{
		ret[i] = ft_strdup(tokken->content);
		tokken = tokken->next;
	}
	ret[i] = NULL;
	return (ret);
}

int	ft_cnt_in_pipe(char *tokken_arr, int num)
{
	int	i;

	i = 0;
	while (tokken_arr[i])
	{
		if (tokken_arr[i] == '|')
			break ;
		i++;
	}
}

char	***ft_change_arr(char *tokken_arr, int pipe_len)
{
	char	***ret;
	int	i;

	ret = malloc(sizeof(char **) * (ft_arr_find_pipe(tokken_arr) + 1));
	while (tokken_arr[i])
	{
		ret[j] = ft_
		i++;
	}
}

void	ft_paser_manager(t_tokken_list *tokken)
{
	int		pipe_len;
	char	*tokken_arr;
	char	***parsing_arr;

	tokken_arr = ft_lst_to_arr(tokken);
	pipe_len = ft_arr_find_pipe(tokken_arr);
	if (pipe_len > 0)
		parsing_arr = ft_change_arr(tokken_arr, pipe_len);
	else if (!pipe_len)
		//
}