#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

void	error_exit(int code)
{
	exit(code);
}

#include <string.h>

int main()
{
	char	*v;
	pid_t	child;

	// set_signals_handlers();
	while(1)
	{
		v = readline("porcodio! ");
		if (!v)
			error_exit(1);
		child = fork();
		if (child == 0) {
			char **argv;

			argv = malloc(sizeof(char *));
			argv[0] = strdup("lol");
			execve("echo ", argv);
			perror("execve");
			exit(EXIT_FAILURE);
		} else {
			printf("spawned child with pid - %d\n", child);
			return child;
		}
	}
	return (0);
}