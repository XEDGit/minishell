/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:37:54 by lmuzio            #+#    #+#             */
/*   Updated: 2022/12/18 10:56:51 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

int	prepend_arg(char *pre, t_cmd *cmd)
{
	int i;
	for (i = 0; cmd->args[i]; i++);

	i += 2;
	char **ret = malloc(i * sizeof(char **));
	if (!ret)
		return error_int("Allocation failed", "exec", 1, EXIT_FAILURE);
	ret[0] = sk_strdup(pre);
	for (i = 0; cmd->args[i]; i++)
		ret[i + 1] = sk_strdup(cmd->args[i]);
	ret[i + 1] = 0;
	free2d(cmd->args, 0);
	cmd->args = ret;
	cmd->cmd = ret[0];
	return (EXIT_SUCCESS);
}

int	execute_cmd(t_cmd *cmd, char **envp)
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
	char *shell_interpreter = "/bin/sh";
	if (!prepend_arg(shell_interpreter, cmd))
		execve(shell_interpreter, cmd->args, envp);
	return (error_int("Failed to execute", cmd->cmd, 1, EXIT_FAILURE));
}

int	parse_cmd(t_cmd *start, t_data *data)
{
	pid_t	child_pid = 0;

	if (start->is_pipe && open_pipe(start))
		return (error_int("failed to open pipe", start->cmd, 1, false));
	if (start->files && open_files(start, data))
		return (false);
	start->cmd = check_paths(data->paths, start->cmd);
	if (start->cmd)
	{
		start->args[0] = start->cmd;
		child_pid = fork();
		if (!child_pid)
			return execute_cmd(start, data->env->envp->mem);
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
		{
			ret = true;
			if (skip)
				*cmd = (*cmd)->next;
		}
		else
			ret = false;
	}
	else if ((*cmd)->conditional == '&')
	{
		if (g_exit_code != 0)
		{
			ret = true;
			if (skip)
				*cmd = (*cmd)->next;
		}
		else
			ret = false;
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
			sk_strjoin(&buffer, (*start)->args[i], false);
			if ((*start)->args[i + 1])
				sk_strjoin(&buffer, " ", false);
			i++;
		}
		if ((*start)->next && (*start)->next->depth >= depth)
		{
			if ((*start)->next->conditional == '|')
				sk_strjoin(&buffer, " || ", false);
			else if ((*start)->next->conditional == '&')
				sk_strjoin(&buffer, " && ", false);
			else if ((*start)->is_pipe)
				sk_strjoin(&buffer, " | ", false);
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

	child_pid = 0;
	piping = 0;
	while (start)
	{
		if (buff_contains(data->env->opts, "VERBOSE", 0) != -1)
		{
			if (start->prev && start->prev->depth == start->depth && \
			start->conditional != -1)
				sk_dprintf(2, "%s -> ", start->conditional == '|'? "||" : "&&");
			int i = 0;
			while (start->args[i])
				sk_dprintf(2, "%s ", start->args[i++]);
			start = start->next;
			if (start)
				sk_dprintf(2, "-> ");
			else
				sk_dprintf(2, "\n");
			continue ;
		}
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
			sk_subshell(buf, data->env, data->aliases, true, 0);
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
			return (2);
		else if (builtin == ERROR)
			return (ERROR);
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
	t_cmd	*start;
	char	*paths;

	paths = env_get(data->env, "PATH", 1);
	data->paths = sk_split(paths, ":");
	if (!data->paths)
		error_int("path allocation failed", "malloc", -1, 0);
	free(paths);
	start = data->cmds;
	signals_handler_setup(1);
	int code = executer_loop(start, data);
	signals_handler_setup(0);
	free2d(data->paths, 0);
	return (code);
}
