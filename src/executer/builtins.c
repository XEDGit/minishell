/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 02:24:53 by lmuzio            #+#    #+#             */
/*   Updated: 2022/09/12 20:05:27 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	exec_builtin(t_cmd *cmd, t_env *envs, int i)
{
	pid_t		pid;
	static int	(*funcs[])(char **args, t_env *env) = {
		&ft_cd, &ft_echo, &ft_export, &ft_unset, &ft_env, &ft_pwd
	};

	pid = fork();
	if (pid)
		return (watch_child(pid));
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	dup2(cmd->redirects[0], 0);
	dup2(cmd->redirects[1], 1);
	dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	if (!ft_strcmp("exit", cmd->cmd))
	{
		if (cmd->args[1] && !cmd->args[2])
			g_exit_code = ft_atoi(cmd->args[1]);
		else if (cmd->args[1] && cmd->args[2])
			error_int("too many arguments", "exit", 1, 0);
		exit(g_exit_code);
	}
	g_exit_code = funcs[i](cmd->args, envs);
	exit(g_exit_code);
}

void	exec_single_builtin(t_cmd *cmd, t_env *env, int i)
{
	static int	(*funcs[])(char **args, t_env *env) = {
		&ft_cd, &ft_echo, &ft_export, &ft_unset, &ft_env, &ft_pwd
	};

	if (cmd->redirects[0] != 0)
		dup2(cmd->redirects[0], 0);
	if (cmd->is_pipe)
		dup2(cmd->redirects[1], 1);
	if (cmd->redirects[2] != 2)
		dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	if (i == 6)
	{
		if (cmd->args[1] && !cmd->args[2])
		{
			g_exit_code = ft_atoi(cmd->args[1]);
			if (g_exit_code == 0 && cmd->args[1][0] != '0')
				error_int("numeric argument required", "exit", 2, 0);
		}
		else if (cmd->args[1] && cmd->args[2])
			error_int("too many arguments", "exit", 1, 0);
	}
	else if (i != 6)
		g_exit_code = funcs[i](cmd->args, env);
}

int	check_builtin(t_cmd *cmd, t_env *env, int piping)
{
	int			i;
	static char	*builtins[] = {
		"cd", "echo", "export", "unset", "env", "pwd", "exit", 0
	};

	i = 0;
//temp command for seeing last exit code
if (cmd->cmd && !ft_strcmp("code", cmd->cmd))
	{
		ft_printf("g_exit_code = %d\n", g_exit_code);
		return (true);
	}
//
	while (builtins[i])
	{
		if (!cmd->cmd || !ft_strcmp(builtins[i++], cmd->cmd))
		{
			if (cmd->is_pipe && open_pipe(cmd))
				return (error_int("Pipe opening failed\n", cmd->cmd, 1, 0));
			if (cmd->cmd && piping)
				exec_builtin(cmd, env, i - 1);
			else if (cmd->cmd)
				exec_single_builtin(cmd, env, i - 1);
			clean_redirects(cmd);
			if (i == 7 && !piping)
				return (2);
			return (true);
		}
	}
	return (false);
}
