/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 05:12:41 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/10 21:26:49 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct s_data
{
	int			(*fds)[2];
	pid_t		*children;
}	t_data;

char	*ft_strdup(char *buf)
{
	char	*res[2];

	if (!buf || !*buf)
		return (0);
	res[0] = malloc(strlen(buf));
	res[1] = res[0];
	while (*buf)
		*(res[0])++ = *buf++;
	return (res[1]);
}

void	error_exit(t_data *data, int i, char *msg)
{
	int	c;

	c = 0;
	while (c < i)
	{
		close(data->fds[c][0]);
		close(data->fds[c][1]);
		c++;
	}
	free(data->children);
	free(data->fds);
	printf("%s, errno: %d", msg, errno);
	exit(errno);
}

void	routine(t_data *data, int i, char **buffer)
{
	*buffer = malloc(12);
	if (!*buffer)
		error_exit(data, i, "Error inside child process at malloc\n");
	if (read(data->fds[i - 1][0], *buffer, 12) < 0)
		error_exit(data, i, "Error inside child process at read\n");
	if (close(data->fds[i - 1][0]) < 0)
		error_exit(data, i, "Error inside child process at close\n");
	printf("%d - %s", i, *buffer);
	if (write(data->fds[i][1], *buffer, 12) < 0)
		error_exit(data, i, "Error inside child process at write_pipe\n");
	if (close(data->fds[i][1]) < 0)
		error_exit(data, i, "Error inside child process at close\n");
}

void	set_redirects(t_data *data, int i)
{
	char		*buffer;
	int			err;

	if (!i)
	{
		buffer = ft_strdup("Porjvfnnco\n");
		if (!buffer)
			error_exit(data, i, "Error inside child process at strdup\n");
		printf("%d - %s", i, buffer);
		if (write(data->fds[i][1], buffer, 12) < 0)
			error_exit(data, i, "Error inside child process at write_pipe\n");
		if (close(data->fds[i][1]) < 0)
			error_exit(data, i, "Error inside child process at close\n");
	}
	else
		routine(data, i, &buffer);
	free(buffer);
	exit(0);
}

int	main(void)
{
	const int	child_num = 300;
	int			i;
	t_data		data;

	i = 0;
	data.fds = malloc(child_num * sizeof(int));
	data.children = malloc(child_num * sizeof(pid_t));
	if (!data.fds || !data.children)
		error_exit(&data, i, "Failed to allocate struct");
	while (i < child_num)
	{
		if (pipe(data.fds[i]) < 0)
			error_exit(&data, i - 1, "Pipe failed to init");
		data.children[i] = fork();
		if (data.children[i] < 0)
			error_exit(&data, i, "Child failed to fork");
		if (!data.children[i])
			set_redirects(&data, i);
		i++;
	}
	close(data.fds[i - 1][0]);
	free(data.fds);
	free(data.children);
	exit(0);
}
