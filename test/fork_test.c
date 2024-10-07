#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdio.h>

void	ft_fork_pipe(char **token_arr)
{
	//int	pipefd[2];
	int	pid1;
	int	pid2;
	//char *const	env[] = {store_path(envp), NULL};

	//if (pipe(pipefd) == -1)
	//	error("pipe_error\n", 1);
	pid1 = fork();
	if (pid1 < 0)
		error("first fork\n", 1);
	else if (pid1 == 0)
	{
		printf("token_arr[0]\n");
		//first_child_process(pipefd, av, env);
	}
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			error("second fork\n", 1);
		else if (pid2 == 0)
		{
			printf("token_arr[1]\n");
			//second_child_process(pipefd, av, env);
		}
		// else
		// 	parents_process(pipefd);
	}
	exit (EXIT_SUCCESS);
}