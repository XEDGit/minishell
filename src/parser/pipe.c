/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:14:41 by nmolinel          #+#    #+#             */
/*   Updated: 2022/10/26 16:14:42 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	set_is_pipe(t_cmd *cmd)
{
	if (cmd->prev->redirects[1] != STDOUT_FILENO && \
		cmd->redirects[0] != STDIN_FILENO)
		return ;
	cmd->prev->is_pipe = true;
}

int	set_pipe_cond(char *tables, t_cmd *cmd)
{
	if (cmd->prev)
	{
		if (*tables != AMP && *tables != PIPE)
			set_is_pipe(cmd);
		else
		{
			cmd->conditional = *tables;
			*tables = ' ';
		}
	}
	return (1);
}
