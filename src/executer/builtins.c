/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 02:24:53 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/12 00:32:47 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	exec_builtin(t_cmd *cmd, char **envp, char **envl, int i)
{
	static int	(*funcs[])(char **args, char **envp, char **envl) = {
		&ft_cd, &ft_echo, &ft_export, &ft_unset, &ft_env, &ft_pwd
	};
	pid_t	pid;

	pid = fork();
	if (pid)
		return (watch_child(pid));
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	if (cmd->redirects[0] != 0)
		dup2(cmd->redirects[0], 0);
	if (cmd->is_pipe)
		dup2(cmd->redirects[1], 1);
	if (cmd->redirects[2] != 2)
		dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	if (!ft_strcmp("exit", cmd->cmd))
	{
		if (cmd->args[1])
			g_exit_code = ft_atoi(cmd->args[1]);
		exit(g_exit_code);
	}
	g_exit_code = funcs[i](cmd->args, envp, envl);
	exit(g_exit_code);
}

void	exec_single_builtin(t_cmd *cmd, char **envp, char **envl, int i)
{
	static int	(*funcs[])(char **args, char **envp, char **envl) = {
	&ft_cd, &ft_echo, &ft_export, &ft_unset, &ft_env, &ft_pwd
	};

	if (cmd->redirects[0] != 0)
		dup2(cmd->redirects[0], 0);
	if (cmd->is_pipe)
		dup2(cmd->redirects[1], 1);
	if (cmd->redirects[2] != 2)
		dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	if (i == 6 && cmd->args[1])
		g_exit_code = ft_atoi(cmd->args[1]);
	else if (i != 6)
		g_exit_code = funcs[i](cmd->args, envp, envl);
}

int	check_builtin(t_cmd *cmd, char **envp, char **envl, int piping)
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
				exec_builtin(cmd, envp, envl, i - 1);
			else if (cmd->cmd)
				exec_single_builtin(cmd, envp, envl, i - 1);
			clean_redirects(cmd);
			if (i == 7 && !piping)
				return (2);
			return (true);
		}
	}
	return (false);
}
