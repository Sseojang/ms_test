/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:25:52 by seojang           #+#    #+#             */
/*   Updated: 2024/09/07 17:49:23 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

		// if (ft_meta == 3) // '<'
		// {
		// 	ft_in_here(line, i);
		// }
		// if (ft_meta == 4) // '>'
		// {
		// 	ft_out_next(line, i);
		// }
		// if (ft_meta == 5) // '|'
		// if (ft_meta == 6) // '$'

void	ft_tokenizer(char *line, char **envp)
{
	//ft_qoute_check(line);
	// ft_find_pipe(line);
	ft_qoute_check(line, envp);
	write(1, "\n", 1);
}