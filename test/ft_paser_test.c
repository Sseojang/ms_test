/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:52:02 by seojang           #+#    #+#             */
/*   Updated: 2024/09/24 20:23:01 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

// 리다이렉션 구현
// < 파일 및 폴더 열기
// << 파일에 들어온 문자가 나올 때 까지 받기
// > 덮어쓰거나 새로만들기
// >> 이어 붙여 만들기

// 파이프 개수 와 토큰 개수 구한 후 2차원 배열 만들기
// 병렬로 프로세스 포크 후 각 프로세스에 배열값 보내기

int	ft_pipe_len(t_tokken_list **tokken)
{
	int	ret;
	t_tokken_list	*temp;

	ret = 0;
	temp = *tokken;
	while (temp)
	{
		if (temp->content == '|')
			ret++;
		temp = temp->next;
	}
	return (ret);
}

void	ft_lst_join(t_tokken_list **tokken, char ***parsing, int i, int j)
{
	int	num;
	t_tokken_list	*temp;

	num = 0;
	parsing[j] = (char **)malloc(sizeof(char *) * i);
	temp = *tokken;
	while (i--)
	{
		parsing[j][num] = ft_strdup(temp->content);
		temp = temp->next;
		num++;
	}
}

char	**ft_paser_maneger(t_tokken_list **tokken)
{
	t_tokken_list	*temp;
	t_tokken_list	*head_node;
	char			***parsing;
	int				pipe_len;
	int				i;
	int				j;

	parsing = NULL;
	parsing = (char ***)malloc(sizeof(char **) * (ft_pipe_len(tokken) + 1));
	temp = *tokken;
	head_node = temp;
	i = 0;
	j = 0;
	while (temp)
	{
		if (temp->content == '|')
		{
			ft_lst_join(head_node, parsing, i, j);
			i = 0;
			j++;
			head_node = temp->next;
		}
		temp = temp->next;
		i++;
	}
}