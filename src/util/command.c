/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:08:34 by nmolinel          #+#    #+#             */
/*   Updated: 2022/11/15 16:39:22 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

//	set default values for command node
void	set_defaults(t_cmd *cmd)
{
	cmd->cmd = 0;
	cmd->args = 0;
	cmd->redirects[0] = STDIN_FILENO;
	cmd->redirects[1] = STDOUT_FILENO;
	cmd->redirects[2] = STDERR_FILENO;
	cmd->is_pipe = 0;
	cmd->conditional = -1;
	cmd->depth = 0;
	cmd->files = 0;
	if (cmd->prev)
	{
		cmd->depth = cmd->prev->depth;
		if (cmd->prev->depth_next != -1)
			cmd->depth = cmd->prev->depth_next;
	}
	cmd->depth_next = -1;
	cmd->next = 0;
}

t_cmd	*last_node(t_cmd *start)
{
	t_cmd	*last;

	last = start;
	while (last->next)
		last = last->next;
	return (last);
}

//	Append new command node to list
t_cmd	*add_cmd(t_cmd **start)
{
	t_cmd	*cmd;
	t_cmd	*last;

	cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (!cmd)
		return (error_msg("cmd malloc fail", -1));
	cmd->prev = 0;
	if (!*start)
		*start = cmd;
	else
	{
		last = last_node(*start);
		last->next = cmd;
		cmd->prev = last;
	}
	set_defaults(cmd);
	return (cmd);
}

//	free memory allocated by a cmd node
void	free_cmd(t_cmd *cmd)
{
	if (cmd->args)
		free2d(cmd->args, 0);
	if (cmd->redirects[0] != STDIN_FILENO)
		close(cmd->redirects[0]);
	if (cmd->redirects[1] != STDOUT_FILENO)
		close(cmd->redirects[1]);
	free_files(cmd->files);
	free(cmd);
}

//	free the entire commands list
int	free_cmds(t_cmd *start, char **table, int exit_code)
{
	t_cmd	*cmd;

	cmd = start;
	while (start)
	{
		cmd = start;
		start = cmd->next;
		free_cmd(cmd);
	}
	if (table)
		free2d(table, 0);
	return (exit_code);
}
