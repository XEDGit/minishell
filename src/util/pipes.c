/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:49:33 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/12 18:53:21 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_realloc(char *src, unsigned int size)
{
	char	*res;

	res = malloc((size + 1) * sizeof(char));
	ft_strlcpy(res, src, ft_strlen(src) + 1);
	free(src);
	return (res);
}

char	*extract_pipe(int fd)
{
	char	*buffer;
	int		buffer_size;
	int		size_mult;
	int		c;

	c = 0;
	size_mult = 1;
	buffer_size = 10;
	buffer = malloc((buffer_size + 1) * sizeof(char));
	buffer[0] = 0;
	while (1)
	{
		if (read(fd, &buffer[(size_mult - 1) * buffer_size + c], 1) < 1)
			break ;
		buffer[(size_mult - 1) * buffer_size + c + 1] = 0;
		if (++c == buffer_size)
		{
			c = 0;
			buffer = ft_realloc(buffer, buffer_size * ++size_mult);
		}
	}
	if (!buffer[0])
	{
		free(buffer);
		return (0);
	}
	return (buffer);
}
