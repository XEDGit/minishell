/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 02:24:53 by lmuzio            #+#    #+#             */
/*   Updated: 2022/12/18 13:28:57 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	exec_builtin(t_cmd *cmd, t_data *data, int i)
{
	pid_t		pid;
	static int	(*funcs[])(t_cmd *cmd, t_data *data) = {
		0,
		&sk_exec,
		&sk_cd,
		&sk_echo,
		&sk_export,
		&sk_unset,
		&sk_env,
		&sk_pwd,
		&sk_source,
		&sk_alias,
		&sk_memdetect,
	};

	if (i == 10)
		return ;
	pid = fork();
	if (pid)
	{
		if (pid != -1)
			watch_child(pid);
		else
			error_int("error forking process", cmd->cmd, 1, 0);
		return ;
	}
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	if (cmd->redirects[0] != 0)
		dup2(cmd->redirects[0], 0);
	if (cmd->redirects[1] != 1)
		dup2(cmd->redirects[1], 1);
	if (cmd->redirects[2] != 2)
		dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	if (!i)
		sk_exit(cmd);
	g_exit_code = funcs[i](cmd, data);
	exit(g_exit_code);
}

void	exec_single_builtin(t_cmd *cmd, t_data *data, int i)
{
	static int	(*funcs[])(t_cmd *cmd, t_data *data) = {
		0,
		&sk_exec,
		&sk_cd,
		&sk_echo,
		&sk_export,
		&sk_unset,
		&sk_env,
		&sk_pwd,
		&sk_source,
		&sk_alias,
		&sk_memdetect,
	};
	t_cmd		fds;

	fds.redirects[0] = dup(0);
	fds.redirects[1] = dup(1);
	fds.redirects[2] = dup(2);
	dup2(cmd->redirects[0], 0);
	dup2(cmd->redirects[1], 1);
	dup2(cmd->redirects[2], 2);
	if (!i)
		sk_exit(cmd);
	g_exit_code = funcs[i](cmd, data);
	if (i != 1)
	{
		dup2(fds.redirects[0], 0);
		dup2(fds.redirects[1], 1);
		dup2(fds.redirects[2], 2);
	}
	clean_redirects(&fds);
}

int	add_envl(t_cmd *cmd, t_env *env)
{
	int	i;

	if (cmd->depth != 0)
		return (true);
	i = 0;
	while (cmd->args[i])
	{
		char	*var_name = sk_strdup(cmd->args[i]);
		if (!var_name)
			return (error_int("Malloc error", "add envp", 1, 1));
		*sk_strchr(var_name, '=') = 0;
		char	*var_exists = env_get(env, var_name, 1);
		free(var_name);
		int		target = 2;
		if (var_exists)
			target = 1;
		free(var_exists);
		if (!env_add(env, cmd->args[i], target))
			error_int("error while adding variable", cmd->cmd, 1, 0);
		i++;
	}
	return (false);
}

int	check_builtin(t_cmd *cmd, t_data *data, int piping)
{
	int			i;
	static char	*builtins[] = {
		"exit",
		"exec",
		"cd",
		"echo",
		"export",
		"unset",
		"env",
		"pwd",
		"source",
		"alias",
		"memdetect",
		0
	};

	i = 0;
	while (cmd->args[i])
	{
		int c = 0;
		while (cmd->args[i][c] && cmd->args[i][c] != '=' && !is_del(cmd->args[i][c++]));
		if (cmd->args[i][0] == '=' || cmd->args[i][c] != '=')
			break ;
		i++;
	}
	if (check_aliases(cmd, data->aliases))
		return (ERROR);
	if (!cmd->args[i] && add_envl(cmd, data->env))
		return (true);
	while (cmd->cmd && sk_strchr(cmd->cmd, '='))
	{
		free(cmd->args[0]);
		i = -1;
		while (cmd->args[++i])
			cmd->args[i] = cmd->args[i + 1];
		cmd->cmd = cmd->args[0];
	}
	i = 0;
	while (builtins[i])
	{
		if (!cmd->cmd || !sk_strcmp(builtins[i], cmd->cmd))
		{
			if (cmd->is_pipe && open_pipe(cmd))
				return (error_int("pipe opening failed\n", cmd->cmd, 1, 0));
			if (cmd->files && open_files(cmd, data))
				return (true);
			if (cmd->cmd && piping)
				exec_builtin(cmd, data, i);
			else if (cmd->cmd)
				exec_single_builtin(cmd, data, i);
			clean_redirects(cmd);
			if (!i && !piping && cmd->cmd)
				return (2);
			if (i == 10)
				return (false);
			return (true);
		}
		i++;
	}
	return (false);
}
