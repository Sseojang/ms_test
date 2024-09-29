# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

void	first_child_process(int *pipefd, char **av, char *const env[])
{
	int	filefd;
	char	*command;
	char	**command_vec;

	close(pipefd[0]);
	command = find_path(av[2], env[0]);
	if (command == NULL)
		error(av[2], 3);
	command_vec = ft_split(av[2], ' ');
	filefd = open(av[1], O_RDONLY);
	if (filefd < 0)
		error(av[1], 2);
	dup2(filefd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(filefd);
	execve(command, command_vec, env);
	error(NULL, 4);
}

int	main(int ac, char **av, char **envp)
{
	int	pipefd[2];
	int	pid1;
	int	pid2;
	char *const env[] = {store_path(envp), NULL};

	if (pipe(pipefd) == -1)
		error("pipe_error\n", 1);
	pid1 = fork();
	if (pid1 < 0)
		error("first fork error\n", 1);
	else if (pid1 == 0)
		first_child_process(pipefd, av, env);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			error("second fork error\n", 1);
		else if (pid2 == 0)
			second_child_process(pipefd, av, env);
		else
			parents_process(pipefd);
	}
	exit(EXIT_SUCCESS);
}