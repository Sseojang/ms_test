#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av, char **envp)
{
	int	i;
	int	j;
	i = 0;
	while (envp[i])
	{
		j = 0;
		if (envp[i][0] == av[1][j])
		{
			while (envp[i][j] != '=')
			{
				if (envp[i][j] == av[1][j])
					j++;
				else
					break ;
			}
			if (envp[i][j] == '=' && av[1][j] == '\0') //변수 있음
			{
				j++;
				while (envp[i][j] != '\0')
					write(1, &envp[i][j++], 1);
				return (0);
			}
		}
		i++;
	}
	printf("");
	return (0);
}