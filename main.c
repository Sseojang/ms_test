#include "ms_test.h"

// void	handler()
// {
// 	exit(0);
// }

int main(char **envp)
{
	char *line;
	char *temp;

	line = NULL;
	//signum(handler);
	while (1)
	{
		line = readline("minishell>");
		if (line)
			ft_tokenizer(line, envp);
		add_history(line);
		free(line);
	}
	return (0);
}