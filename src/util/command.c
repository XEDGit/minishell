#include <minishell.h>

//	set default values for command node
void	set_defaults(t_cmd *cmd)
{
	cmd->cmd = 0;
	cmd->args = 0;
	cmd->redirects[0] = STDIN_FILENO;
	cmd->redirects[1] = STDOUT_FILENO;
	cmd->redirects[2] = STDERR_FILENO;
	cmd->par_depth = 0;
	cmd->conditional = -1;
	cmd->prev = 0;
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
		return (error_msg("cmd malloc fail"));
	set_defaults(cmd);
	if (!*start)
		*start = cmd;
	else
	{
		last = last_node(*start);
		last->next = cmd;
		cmd->prev = last;
	}
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
	free(cmd);
}

//	free the entire commands list
int	free_cmds(t_cmd *start, char **table, int exit_code)
{
	while (start)
	{
		free_cmd(start);
		start = start->next;
	}
	if (table)
		free2d(table, 0);
	return (exit_code);
}

int	debug_cmds(t_cmd *start)
{
	int	i;
	int	c;

	i = 0;
	while (start)
	{
		c = -1;
		printf("\n--COMMAND %d -> %s -------------------\n--ARGS", i++, start->cmd);
		while (start->args && start->args[++c])
			printf("\t[%d]%s\t|", c, start->args[c]);
		printf("\n--IN: %d\n--OUT: %d\n", start->redirects[0], start->redirects[1]);
		printf("--COND: %d\n--DEPTH: %d\n", start->conditional, start->par_depth);
		start = start->next;
	}
	return (0);
}
