#include "ms_test.h"

void	ft_print(char *line)
{
	printf("%s", line);
}

void	ft_print_export(char *temp, char **envp)
{
	int	i;
	int	j;
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
					write(1, &envp[i][j++], 1);
				break ;
			}
		}
		i++;
	}
}

int	ft_export_check(char *line, int i, char **envp)
{
	char	*temp;
	int		first_num;

	first_num = i;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '"')
			temp = ft_substr(line, first_num, i);
	}
	ft_print_export(temp, envp);
	return () //변수 없음
}

int	ft_double_qoute(char *line, int i, char **envp)
{
	i++;
	int	d_qoute_flag;

	d_qoute_flag = 1;
	while (line[i])
	{
		if (line[i] == '$')
			ft_export_check(line, i, envp);
		if (line[i] == 34)
			return (i);
	}
	if (d_qoute_flag)
		exit(0);
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
		exit(0);
	else
		return (i);
}

void	ft_qoute_check(char *line, char **envp)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39) //싱글 쿼트
		{
			i = ft_single_qoute(line, i);
		}
		else if (line[i] == 34) //더블 쿼트
		{
			i = ft_double_qoute(line, i, envp);
		}
		else
			write(1, &line[i], 1);
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

void	ft_tokenizer(char *line, char **envp)
{
	//ft_qoute_check(line);
	// ft_find_pipe(line);
	ft_qoute_check(line, envp);
}