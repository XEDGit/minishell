/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:22:13 by lmuzio            #+#    #+#             */
/*   Updated: 2022/09/03 19:16:44 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>
#include <shared.h>

void	execute_cmd(t_cmd *cmd, char **envp)
{
	int	exit_code;

	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	if (cmd->redirects[0] != 0)
		dup2(cmd->redirects[0], 0);
	if (cmd->is_pipe)
		dup2(cmd->redirects[1], 1);
	if (cmd->redirects[2] != 2)
		dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	execve(cmd->cmd, cmd->args, envp);
}

int	parse_cmd(t_cmd *start, char **envp)
{
	pid_t	child_pid;

	start->cmd = start->args[0];
	if (start->is_pipe && open_pipe(start))
		return (error_int("pipe command failed\n", 0));
	child_pid = fork();
	if (!child_pid)
		execute_cmd(start, envp);
	if (start->next && start->next->conditional != -1)
		while (wait(0) != -1)
			;
	clean_redirects(start);
	return (0);
}

int	executer(t_data *data)
{
	char	*new_cmd;
	t_cmd	*start;

	data->paths = ft_split(getenv("PATH"), ":");
	start = data->cmds;
	signals_handler_setup(1);
	while (start)
	{
		start->args[0] = check_paths(data->paths, start->cmd);
		if (start->args[0] != NULL)
			parse_cmd(start, data->envp);
		start = start->next;
	}
	while (wait(0) != -1)
		;
	return (0);
}
