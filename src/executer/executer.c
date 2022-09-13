/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:22:13 by lmuzio            #+#    #+#             */
/*   Updated: 2022/09/12 20:08:21 by lmuzio           ###   ########.fr       */
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
	char    *new_paths;

	start->args[0] = check_paths(data->paths, start->cmd);
	start->cmd = start->args[0];
	if (start->is_pipe && open_pipe(start))
		return (false);
	if (start->args[0])
	{
		child_pid = fork();
		if (!child_pid)
			execute_cmd(start, data->env->envp->mem);
		if (start->next && start->next->conditional != -1)
		{
			watch_child(child_pid);
			new_paths = env_get(data->env, "PATH", 0);
			free2d(data->paths, 0);
			data->paths = ft_split(new_paths, ":");
			free(new_paths);	
		}
	}
	clean_redirects(start);
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
		if (!set_redirects(start, data->heredocs))
		{
			start = start->next;
			continue ;
		}
		builtin = 0;
		builtin = check_builtin(start, data->env, piping);
		if (builtin == 2)
			return (true);
		if (!builtin)
			child_pid = parse_cmd(start, data);
		start = start->next;
	}
	watch_child(child_pid);
	return (false);
}

int	executer(t_data *data)
{
	int		piping;
	pid_t	child_pid;
	t_cmd	*start;
	char	*paths;

	paths = env_get(data->env, "PATH", 0);
	data->paths = ft_split(paths, ":");
	free(paths);
	start = data->cmds;
	signals_handler_setup(1);
	if (executer_loop(start, data))
		return (2);
	signals_handler_setup(0);
	free2d(data->paths, 0);
	return (0);
}
