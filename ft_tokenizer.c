#include "ms_test.h"

void	ft_print(char *line)
{
	printf("%s", line);
}

int	ft_export_check(char *line, int i, char **envp)
{
	char	*temp;
	int		first_num;

	first_num = i;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			temp = ft_substr(line, first_num, i);
	}
	int	i;
	int	j;
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (envp[i][0] == temp [0])
		{
			if (ft_strcmp(envp[i], temp) == 0);
				return ()//변수 존재
		}
		i++;
	}
	return () //변수 없음
}

int	ft_double_qoute(char *line, int i)
{
	i++;
	int	d_qoute_flag;

	d_qoute_flag = 1;
	while (line[i])
	{
		if (line[i] == '$')
		{
			ft_export_check();
		}
		if (line[i] == 34)
			return (i);
	}
	if (d_qoute_flag)
		return (-1);
	else
		return (i);
}

int	ft_single_qoute(char *line, int i)
{
	i++;
	int	s_qoute_flag;

	s_qoute_flag = 1;
	while (line[i])
	{
		if (line[i] == 39)
			return (i);
		i++;
	}
	if (s_qoute_flag)
		return (-1);
	else
		return (i);
}

void	ft_qoute_check(char *line)
{
	int	i;
	int	s_qoute_flag;
	int	d_qoute_flag;

	i = 0;
	s_qoute_flag = 0;
	d_qoute_flag = 0;
	while (line[i])
	{
		if (line[i] == 39) //싱글 쿼트
		{
			i = ft_single_qoute(line, i);
		}
		if (line[i] == 34) //더블 쿼트
		{
			i = ft_double_qoute(line, i);
		}
		i++;
	}
}

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

void	ft_tokenizer(char *line)
{
	//ft_qoute_check(line);
	// ft_find_pipe(line);
	ft_qoute_check(line);
}