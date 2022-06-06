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
			printf("heredoc pipe[%d]: %s\n", c, buffer);
			free(buffer);
		}
		c++;
	}
}

int	set_data(char *input, t_cmd *cmd)
{
	printf("Split input: %s$\n", input);
	cmd->args = ft_split(input, " ");
	if (!cmd->args)
		return (error_int("Split fail", 0));
	cmd->cmd = cmd->args[0];
	return (1);
}

int	set_pipes_cond(char *tables, t_cmd *cmd)
{
	int	fd[2];

	if (cmd->prev)
	{
		if (*tables != AMP && *tables != PIPE)
		{
			if (pipe(fd) == ERROR)
				return (error_int("Pipe failed", 0));
			cmd->redirects[0] = fd[0];
			if (cmd->prev->redirects[1] == STDOUT_FILENO)
				cmd->prev->redirects[1] = fd[1];
		}
		else
		{
			cmd->conditional = *tables;
			*tables = ' ';
		}
	}
	return (1);
}

int	p_setter(t_cmd **lst, char *table, int **docs)
{
	t_cmd	*cmd;
	char	*rest;

	cmd = add_cmd(lst);
	if (cmd && \
	set_pipes_cond(table, cmd) && \
	set_redirects(table, cmd, docs) && \
	set_data(table, cmd))
		return (1);
	return (0);
}

// INPUT: <<word  or <file
// OUTPUT: >file or >>file
int	parser(char **tables, t_data *data)
{
	t_cmd	*start;
	char	**to_free;

	start = 0;
	to_free = tables;
	here_docs_db(tables, data);
	while (*tables)
	{
		if (!p_setter(&start, *tables, data->heredocs))
			return (free_cmds(start, to_free, 0));
		tables++;
	}
	data->cmds = start;
	if (PARSE_DEBUG)
		debug_cmds(data->cmds);
	free_cmds(start, to_free, 0);
	return (0);
}
