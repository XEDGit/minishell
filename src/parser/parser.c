/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:22:54 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/12 19:00:19 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parser(char **tables, t_data *data)
{
	int		c;
	char	*buffer;

	c = -1;
	while (tables[++c])
		printf("split[%d]: %s\n", c, tables[c]);
	free2d(tables, 0);
	if (!data->heredoc_c)
		return (0);
	printf("--heredoc count: %d---------------------------\n", data->heredoc_c);
	c = 0;
	while (data->heredocs[c])
	{
		buffer = extract_pipe(data->heredocs[c][0]);
		if (buffer)
		{
			printf("heredoc pipe[%d]: %s\n", c, buffer);
			free(buffer);
		}
		close(data->heredocs[c][0]);
		c++;
	}
	return (0);
}
