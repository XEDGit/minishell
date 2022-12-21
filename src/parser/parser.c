/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 20:22:54 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/11/02 15:28:56 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	set_data(char *input, t_cmd *cmd)
{
	int		i;
	char	*temp;

	cmd->args = sk_split(input, " ");
	if (!cmd->args)
		return (error_int("parser split fail", cmd->cmd, 1, 0));
	i = 1;
	while (cmd->args[0] && is_redirect(cmd->args[0]))
	{
		temp = cmd->args[0];
		cmd->args[0] = cmd->args[i];
		cmd->args[i++] = temp;
	}
	cmd->cmd = cmd->args[0];
	return (1);
}

int	p_setter(t_cmd **lst, char **tables, t_data *data)
{
	t_cmd	*cmd;

	cmd = add_cmd(lst);
	if (cmd && \
	expander(tables, data) && \
	set_pipe_cond(*tables, cmd) && \
	set_redirects(*tables, cmd) && \
	set_data(*tables, cmd) && \
	clean_quotes(cmd))
		return (1);
	return (0);
}

// INPUT: <<word  or <file
// OUTPUT: >file or >>file
int	parser(char **tables, t_data *data)
{
	t_cmd	*cmds;
	int		exit;
	char	**to_free;

	cmds = 0;
	exit = 0;
	to_free = tables;
	while (*tables)
	{
		if (!p_setter(&cmds, tables, data))
			return (free_cmds(cmds, to_free, -1));
		tables++;
	}
	data->cmds = cmds;
	if (executer(data))
		exit = 2;
	free_cmds(cmds, to_free, 0);
	return (exit);
}
