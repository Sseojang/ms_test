#include "ms_test.h"

void	ft_print(char *line)
{
	printf("%s", line);
}

void	ft_find_pipe(char *line)
{
	int i;
	int num;
	int	len;
	char *temp;
	int pipe_flag;


	i = 0;
	num = 0;
	len = 0;
	pipe_flag = 0;
	temp = NULL;
	while (line[i])
	{
		if (line[i] == '|' || (line[i + 1] == '\0' && pipe_flag  == 1))
		{
			temp = ft_substr(line, num, i);
			num = i;
			pipe_flag++;
			ft_print(temp);
			temp = NULL;
		}
		i++;
	}
	if (!pipe_flag)
		printf("%s", line);
	printf("\n");
}

int		ft_qoute_check(char *line)
{
	int	i;
	int	qoute_flag;

	i = 0;
	qoute_flag == 0;
	while (line[i])
	{
		if (line)
	}
	return (0);
}

void	ft_tokenizer(char *line)
{
	ft_qoute_check(line);
	ft_find_pipe(line);
}