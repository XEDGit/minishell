/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 18:49:33 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/15 00:41:01 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Returns 0 on error and the number of copied bytes on success 
src gets freed and replaces with reallocated string */
char	*ft_realloc(char **src, unsigned int new_size)
{
	char	*res;

	res = malloc((new_size + 1) * sizeof(char));
	if (!res)
		return (0);
	ft_strlcpy(res, *src, ft_strlen(*src) + 1);
	free(*src);
	*src = res;
	return (res);
}

// Returns 0 on error or a string with the first char read on success
char	*check_fd(int fd, int buffer_size, char **buffer)
{
	int		read_ret;

	*buffer = malloc((buffer_size + 1) * sizeof(char));
	if (!*buffer)
		return (0);
	read_ret = read(fd, *buffer, 1);
	if (read_ret == ERROR)
	{
		free(*buffer);
		return (0);
	}
	if (!read_ret)
		(*buffer)[0] = 0;
	(*buffer)[1] = 0;
	return (*buffer);
}

// Returns 0 on error or string pipe content
char	*extract_pipe(int fd)
{
	char	*buffer;
	int		size_mult;
	int		c;
	int		read_ret;

	c = 1;
	size_mult = 1;
	if (!check_fd(fd, 10, &buffer))
		return (0);
	while (1)
	{
		read_ret = read(fd, &buffer[(size_mult - 1) * 10 + c], 1);
		buffer[(size_mult - 1) * 10 + c + 1] = 0;
		if (!read_ret)
			break ;
		else if (read_ret == ERROR)
			return (0);
		if (++c == 10)
		{
			c = 0;
			if (!ft_realloc(&buffer, 10 * ++size_mult))
				return (0);
		}
	}
	return (buffer);
}
