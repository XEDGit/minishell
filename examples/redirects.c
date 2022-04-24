#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_data
{
	char	*command;
	char	**args;
	int		redirects[3];
}	t_data;

int main(int argc, char **argv,  char **envp)
{
	const int	child_num = 2;
	int			fd[2];
	pid_t		child;
	int			i;
	t_data		*commands;

	//  Creating pipe
	if (pipe(fd) == -1)
		exit(1);

	commands = malloc(sizeof(t_data) * child_num);

	// Assigning first command table
	commands[0].command = "/usr/bin/ls";
	commands[0].args = malloc(sizeof(char *) * 3);
	commands[0].args[0] = strdup("ls");
	commands[0].args[1] = strdup("-a");
	commands[0].args[2] = 0;
	commands[0].redirects[0] = 0;
	commands[0].redirects[1] = fd[1];
	commands[0].redirects[2] = 2;

	// Assigning sencond command table
	commands[1].command = "/usr/bin/grep";
	commands[1].args = malloc(sizeof(char *) * (child_num + 1));
	commands[1].args[0] = strdup("grep");
	commands[1].args[1] = strdup("p");
	commands[1].args[2] = 0;
	commands[1].redirects[0] = fd[0];
	commands[1].redirects[1] = 1;
	commands[1].redirects[2] = 2;

	i = 0;
	while (i < child_num)
	{
		child = fork();
		if (!child)
		{
			printf("Debug values: %d - %s	%s	0<%d 1>%d 2>%d\n", i,  commands[i].command, commands[i].args[0], commands[i].redirects[0], commands[i].redirects[1], commands[i].redirects[2]);
			dup2(commands[i].redirects[0], 0);
			dup2(commands[i].redirects[1], 1);
			dup2(commands[i].redirects[2], 2);
			if (close(fd[0]) == -1)
				printf("error");
			if (close(fd[1]) == -1)
				printf("error");
			if (execve(commands[i].command, commands[i].args, envp) == -1)
				exit(1);
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}
