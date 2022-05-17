/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:57:51 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/17 17:02:57 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int	main(int argc, char **argv, char **envp)
{
	const char	*path = "/bin/";
	char		*buffer;
	char		**args;

	if (argc < 2)
		exit(1);
	args = malloc(argc * sizeof(char *));
	buffer = malloc(strlen(argv[1]) + strlen(path) + 1);
	buffer[strlen(argv[1]) + strlen(path)] = '\0';
	strcpy(buffer, path);
	strcpy(&buffer[strlen(path)], argv[1]);
	args[argc - 1] = 0;
	while (--argc > 0)
		args[argc - 1] = argv[argc];
	args[0] = buffer;
	if (execve(buffer, args, envp) == -1)
		exit(printf("%d", errno));
	exit(0);
}
