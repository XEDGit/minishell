/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 19:22:13 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/03 14:54:58 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

int	execute_cmd(t_cmd *cmd)
{
	int	exit_code;

	signals_handler_setup(1);
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	if (cmd->redirects[0] != 0)
		dup2(cmd->redirects[0], 0);
	if (cmd->is_pipe)
		dup2(cmd->redirects[1], 1);
	if (cmd->redirects[2] != 2)
		dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	execve(cmd->cmd, cmd->args, 0);
}

int	executer(t_data *data)
{
	pid_t	child_pid;
	char	*new_cmd;
	t_cmd	*start;

	data->paths = ft_split(getenv("PATH"), ":");
	start = data->cmds;
	signals_handler_setup(1);
	while (start)
	{
		start->args[0] = check_paths(data->paths, start->cmd);
		if (start->args[0] != NULL)
		{
			start->cmd = start->args[0];
			if (start->is_pipe)
				open_pipe(start);
			child_pid = fork();
			if (!child_pid)
				execute_cmd(start);
			clean_redirects(start);
		}
		start = start->next;
	}
	while (wait(0) != -1) // make function to watch on child exit code-status
		;
	return (0);
}
