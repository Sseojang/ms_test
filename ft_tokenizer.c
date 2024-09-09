/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:25:52 by seojang           #+#    #+#             */
/*   Updated: 2024/09/09 00:07:46 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_in_pipe(char *line, t_flag flag)
{
	// 파이프로 스플릿 하는데 쿼트는 스킵 하면서 나누기
	// 파이프로 스플릿 후 파싱
	
	// pipex_bonus + 리다이렉션
}

void	ft_noe_pipe(char *line, t_flag flag)
{
	// 리다이렉션 및 execve
}

void	ft_tokenizer(char *line, char **envp)
{
	t_flag	flag;

	ft_qoute_check(line, envp, flag);
	write(1, "\n", 1);
	if (flag->pipe == 1)
		ft_in_pipe(line, flag);
	else
		ft_none_pipe(line, flag);
}