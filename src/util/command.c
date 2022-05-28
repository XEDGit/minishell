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
	cmd->next = 0;
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
		last = *start;
		while (last->next)
			last = last->next;
		last->next = cmd;
	}
	return (cmd);
}

//	free memory allocated by a cmd node
void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
		free2d(cmd->args, 0);
	if (cmd->redirects[0] != STDIN_FILENO)
		close(cmd->redirects[0]);
	if (cmd->redirects[1] != STDOUT_FILENO)
		close(cmd->redirects[1]);
	free(cmd);
}

//	free the entire commands list
int	free_cmds(t_cmd *start, int exit_code)
{
	while (start)
	{
		free_cmd(start);
		start = start->next;
	}
	return (exit_code);
}

int	print_cmds(t_cmd *start)
{
	int	i;
	int	c;

	i = 0;
	while (start)
	{
		c = 0;
		printf("\nCommand %d \n", i++);
		printf("Cmd: %s\n", start->cmd);
		printf("ARGS: ");
		while (start->args && start->args[c])
			printf("%s\t", start->args[c++]);
		printf("\nIN: %d\nOUT: %d\n", start->redirects[0], start->redirects[1]);
		start = start->next;
	}
	return (0);
}
