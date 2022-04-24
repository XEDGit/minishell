#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv, char **envp)
{
	const char	*path = "/usr/bin/";
	char		*buffer;
	char		*args[] = {"ls","-a",NULL,};

	if (argc < 2)
		exit(1);
	// args = malloc((argc + 1) * sizeof(char *));
	buffer = malloc(strlen(argv[1]) + strlen(path) + 1);
	buffer[strlen(argv[1]) + strlen(path)] = '\0';
	strcpy(buffer, path);
	strcpy(&buffer[strlen(path)], argv[1]);
	printf("%s\n", buffer);
	// args[argc] = 0;
	// while (--argc > 0)
	// 	args[argc - 1] = argv[argc];
	argc = 0;
	// while (args[argc])
	// 	printf("%s\n", args[argc++]);
	if (execve(buffer, args, envp) == -1)
		exit(printf("%d", errno));
	exit(0);
}