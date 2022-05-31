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

int		set_data(char *input, t_cmd *cmd)
{
	cmd->args = ft_split(input, " ");
	if (!cmd->args)
	{
		free(input);
		return (error_int("Split fail", 0));
	}
	cmd->cmd = cmd->args[0];
	free(input);
	return (1);
}

int		set_data(char *input, t_cmd *cmd)
{
	char	*to_free;

	to_free = input;
	if (!set_cmd(cmd, &input))
	{
		free(to_free);
		return (0);
	}
	if (*input)
	{
		cmd->args = ft_split(input, " ");
		if (!cmd->args)
		{
			free(to_free);
			return (error_int("Split fail", 0));
		}
	}
	free(to_free);
	return (1);
}

// INPUT: <<word  or <file
// OUTPUT: >file or >>file
int	parser(char **tables, t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*start;
	char	**to_free;
	char	*rest;

	start = 0;
	to_free = tables;
	here_docs_db(tables, data);
	while (*tables)
	{
		cmd = add_cmd(&start);
		if (!cmd)
			return (free_cmds(start, 0));
		rest = set_redirects(*tables, cmd, data->heredocs);
		if (!rest)
			return (free_cmds(start, 0));
		if (!set_data(rest, cmd))
			return (free_cmds(start, 0));
		tables++;
	}
	data->cmds = start;
	print_cmds(data->cmds);
	free2d(to_free, 0);
	free_cmds(start, 0);
	return (0);
}
