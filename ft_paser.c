/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:31:18 by seojang           #+#    #+#             */
/*   Updated: 2024/10/02 18:59:19 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

int	find_pipe(t_tokken_list *tokken)
{
	int	ret;

	ret = 0;
	while (tokken)
	{
		if (tokken->content == '|')
			ret++;
		tokken = tokken->next;
	}
	return (ret);
}

int	lst_len(t_tokken_list *tokken)
{
	int	ret;

	ret = 0;
	while (tokken)
	{
		if (tokken->content == '|')
			break ;
		ret++;
	}
	return (ret);
}

void	lst_join(t_tokken_list *tokken, char **lst_arr)
{
	
}

char	***ft_lst_join(t_tokken_list *tokken, int i)
{
	char	***lst_arr;
	int		arr_num;

	arr_num = 0;
	lst_arr = malloc(sizeof(char **) * i);
	while (tokken)
	{
		if (tokken->content == '|')
			arr_num++;
		lst_arr[arr_num] = (char **)malloc(sizeof(char *) * lst_len(tokken));
		
		tokken = tokken->next;
	}
}

void	ft_paser_manager(t_tokken_list *tokken)
{
	int	i;

	i = find_pipe(tokken);
	if (i > 0)
		;
}