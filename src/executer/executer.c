/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:37:54 by lmuzio            #+#    #+#             */
/*   Updated: 2022/10/26 17:47:47 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	execute_cmd(t_cmd *cmd, char **envp)
{
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	dup2(cmd->redirects[0], 0);
	dup2(cmd->redirects[1], 1);
	dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	execve(cmd->cmd, cmd->args, envp);
}

int	parse_cmd(t_cmd *start, t_data *data)
{
	pid_t	child_pid;

	if (start->is_pipe && open_pipe(start))
		return (error_int("Failed to open pipe", start->cmd, 1, false));
	if (start->files && open_files(start, data))
		return (false);
	start->cmd = check_paths(data->paths, start->cmd);
	if (start->cmd)
	{
		start->args[0] = start->cmd;
		child_pid = fork();
		if (!child_pid)
			execute_cmd(start, data->env->envp->mem);
		if (start->next && start->next->conditional != -1)
		{
			watch_child(child_pid);
			if (!reset_path(data))
				ft_dprintf(2, SHELLNAME"error allocating PATH\n");
		}
	}
	clean_redirects(start);
	if (!start->cmd)
		return (0);
	return (child_pid);
}

int	condition_check(t_cmd **cmd, int *piping)
{
	int	ret;

	*piping = false;
	if ((*cmd)->conditional == '|')
	{
		if (g_exit_code == 0)
			ret = true;
		else
			ret = false;
	}
	else if ((*cmd)->conditional == '&')
	{
		if (g_exit_code != 0)
			ret = true;
		else
			ret = false;
	}
	if (ret)
		*cmd = (*cmd)->next;
	return (ret);
}

int	executer_loop(t_cmd *start, t_data *data)
{
	int		builtin;
	int		piping;
	pid_t	child_pid;

	piping = 0;
	while (start)
	{
		if (start->is_pipe)
			piping = start->is_pipe;
		if (start->conditional != -1 && condition_check(&start, &piping))
			continue ;
		builtin = 0;
		builtin = check_builtin(start, data, piping);
		if (builtin == 2)
			return (true);
		if (!builtin)
			child_pid = parse_cmd(start, data);
		start = start->next;
	}
	if (child_pid)
		watch_child(child_pid);
	return (false);
}

int	executer(t_data *data)
{
	int		ret;
	pid_t	child_pid;
	t_cmd	*start;
	char	*paths;

	ret = 0;
	paths = env_get(data->env, "PATH", 0);
	data->paths = ft_split(paths, ":");
	free(paths);
	start = data->cmds;
	signals_handler_setup(1);
	if (executer_loop(start, data))
		ret = 2;
	signals_handler_setup(0);
	free2d(data->paths, 0);
	return (ret);
}
