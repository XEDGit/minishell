/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 19:22:13 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/02 18:40:35 by lmuzio        ########   odam.nl         */
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
	exit(execve(cmd->cmd, cmd->args, 0));
}

int	executer(t_data *data)
{
	pid_t	child_pid;
	char	*new_cmd;

	data->paths = ft_split(getenv("PATH"), ":");
	signals_handler_setup(1);
	while (data->cmds)
	{
		new_cmd = check_paths(data->paths, data->cmds->cmd);
		if (new_cmd != NULL)
		{
			data->cmds->cmd = new_cmd;
			if (data->cmds->is_pipe)
				open_pipe(data->cmds);
			child_pid = fork();
			if (!child_pid)
				execute_cmd(data->cmds);
			free(data->cmds->cmd);
			clean_redirects(data->cmds);
		}
		data->cmds = data->cmds->next;
	}
	while (wait(0) != -1) // make function to watch on child exit status
		;
	signals_handler_setup(0);
	return (0);
}
