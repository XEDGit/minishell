/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 02:24:53 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/11/02 17:38:58 by nmolinel      ########   odam.nl         */
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
	{
		if (pid != -1)
			watch_child(pid);
		else
			error_int("Error forking process", cmd->cmd, 1, 0);
		return ;
	}
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	dup2(cmd->redirects[0], 0);
	dup2(cmd->redirects[1], 1);
	dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	if (i == 6)
		ft_exit(cmd);
	g_exit_code = funcs[i](cmd->args, envs);
	exit(g_exit_code);
}

void	exec_single_builtin(t_cmd *cmd, t_env *env, int i)
{
	static int	(*funcs[])(char **args, t_env *env) = {
		&ft_cd, &ft_echo, &ft_export, &ft_unset, &ft_env, &ft_pwd
	};
	t_cmd		fds;

	fds.redirects[0] = dup(0);
	fds.redirects[1] = dup(1);
	fds.redirects[2] = dup(2);
	dup2(cmd->redirects[0], 0);
	dup2(cmd->redirects[1], 1);
	dup2(cmd->redirects[2], 2);
	if (cmd->is_pipe)
		clean_redirects(cmd);
	if (i == 6)
		ft_exit(cmd);
	g_exit_code = funcs[i](cmd->args, env);
	dup2(fds.redirects[0], 0);
	dup2(fds.redirects[1], 1);
	dup2(fds.redirects[2], 2);
	clean_redirects(&fds);
}

int	check_builtin(t_cmd *cmd, t_data *data, int piping)
{
	int			i;
	static char	*builtins[] = {
		"cd", "echo", "export", "unset", "env", "pwd", "exit", 0
	};

	i = 0;
	while (builtins[i])
	{
		if (!cmd->cmd || !ft_strcmp(builtins[i++], cmd->cmd))
		{
			if (cmd->is_pipe && open_pipe(cmd))
				return (error_int("Pipe opening failed\n", cmd->cmd, 1, 0));
			if (cmd->files && open_files(cmd, data))
				return (true);
			if (cmd->cmd && piping)
				exec_builtin(cmd, data->env, i - 1);
			else if (cmd->cmd)
				exec_single_builtin(cmd, data->env, i - 1);
			clean_redirects(cmd);
			if (i == 7 && !piping)
				return (2);
			return (true);
		}
	}
	return (false);
}
