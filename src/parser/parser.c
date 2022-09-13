/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 20:22:54 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/12 00:41:18 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	here_docs_db(char **tables, t_data *data)
{
	int		c;
	char	*buffer;

	c = -1;
	while (tables[++c])
		printf("table[%d]: %s\n", c, tables[c]);
	if (!data->heredoc_c)
		return ;
	printf("--heredoc count: %d---------------------------\n", data->heredoc_c);
	c = 0;
	while (data->heredocs[c])
	{
		buffer = extract_pipe(data->heredocs[c][0]);
		if (buffer)
		{
			ft_dprintf(2, "heredoc pipe[%d]: %s\n", c, buffer);
			free(buffer);
		}
		c++;
	}
}

int	set_data(char *input, t_cmd *cmd)
{
	cmd->args = ft_split(input, " ");
	if (!cmd->args)
		return (error_int("Parser split fail", cmd->cmd, 1, 0));
	cmd->cmd = cmd->args[0];
	return (1);
}

int	p_setter(t_cmd **lst, char **tables, int **docs)
{
	t_cmd	*cmd;
	char	*rest;

	cmd = add_cmd(lst);
	if (cmd && \
	expander(tables, cmd) && \
	set_pipe_cond(*tables, cmd) && \
	set_data(*tables, cmd))
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
	// here_docs_db(tables, data);
	while (*tables)
	{
		if (!p_setter(&cmds, tables, data->heredocs))
			return (free_cmds(cmds, to_free, -1));
		tables++;
	}
	data->cmds = cmds;
	// if (PARSE_DEBUG)
		debug_cmds(data->cmds);
	if (executer(data))
		exit = 2;
	free_cmds(cmds, to_free, 0);
	return (exit);
}
