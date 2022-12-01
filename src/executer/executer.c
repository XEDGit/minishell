/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 13:37:54 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/11/02 15:27:26 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	execute_cmd(t_cmd *cmd, char **envp)
{
	signals_handler_setup(2);
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	if (cmd->redirects[0] != 0)
		dup2(cmd->redirects[0], 0);
	if (cmd->redirects[1] != 1)
		dup2(cmd->redirects[1], 1);
	if (cmd->redirects[2] != 2)
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
		if (parent_behaviour(start, data, child_pid))
			return (0);
	}
	clean_redirects(start);
	if (!start->cmd)
		return (0);
	return (child_pid);
}

int	condition_check(t_cmd **cmd, int *piping, int skip)
{
	int	ret;

	*piping = false;
	ret = false;
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
	if (ret && skip)
	{
		while (*cmd && (*cmd)->conditional == '|')
			*cmd = (*cmd)->next;
	}
	return (ret);
}

char	*extract_parenthesis(t_cmd **start)
{
	char	*buffer;
	int		depth;
	int		i;

	depth = (*start)->depth;
	buffer = malloc(1);
	if (!buffer)
		return (0);
	*buffer = 0;
	while (*start && (*start)->depth >= depth)
	{
		i = 0;
		while ((*start)->args[i])
		{
			ft_strjoin(&buffer, (*start)->args[i], false);
			if ((*start)->args[i + 1])
				ft_strjoin(&buffer, " ", false);
			i++;
		}
		if ((*start)->next && (*start)->next->depth >= depth)
		{
			if ((*start)->next->conditional == '|')
				ft_strjoin(&buffer, " || ", false);
			else if  ((*start)->next->conditional == '&')
				ft_strjoin(&buffer, " && ", false);
			else if  ((*start)->is_pipe)
				ft_strjoin(&buffer, " | ", false);
		}
		(*start) = (*start)->next;
	}
	return (buffer);
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
		if (start->prev && start->prev->depth == start->depth && \
		start->conditional != -1 && condition_check(&start, &piping, true))
			continue ;
		if (start->prev && start->prev->depth < start->depth)
		{
			if (condition_check(&start, &piping, false))
			{
				int depth = start->depth;
				while (start && start->depth == depth)
					start = start->next;
				continue ;
			}
			char *buf = extract_parenthesis(&start);
			subshell(buf, data->env, data->aliases, true);
			free(buf);
			if (!start)
				continue ;
			int depth = start->depth;
			while (start && start->depth == depth)
				start = start->next;
			continue ;
		}
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
	t_cmd	*start;
	char	*paths;

	ret = 0;
	paths = env_get(data->env, "PATH", 0);
	data->paths = ft_split(paths, ":");
	if (!data->paths)
		error_int("path allocation failed", "malloc", -1, 0);
	free(paths);
	start = data->cmds;
	signals_handler_setup(1);
	if (executer_loop(start, data))
		ret = 2;
	signals_handler_setup(0);
	free2d(data->paths, 0);
	return (ret);
}
