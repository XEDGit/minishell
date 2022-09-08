/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 02:24:53 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/07 22:00:47 by xed           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	exec_builtin(t_cmd *cmd, char **envp, char **envl, int i)
{
	static int	(*funcs[])(char **args, char **envp, char **envl) = {
		&ft_cd, &ft_echo, &ft_export, &ft_unset, &ft_env, &ft_pwd
	};

	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	if (cmd->redirects[0] != 0)
		dup2(cmd->redirects[0], 0);
	if (cmd->is_pipe)
		dup2(cmd->redirects[1], 1);
	if (cmd->redirects[2] != 2)
		dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	g_exit_code = funcs[i](cmd->args, envp, envl);
	exit(g_exit_code);
}

int	check_builtin(t_cmd *cmd, char **envp, char **envl)
{
	int			i;
	static char	*builtins[] = {
		"cd", "echo", "export", "unset", "env", "pwd", 0
	};

	i = 0;
	if (!ft_strcmp("exit", cmd->cmd))
	{
		if (cmd->args[1])
			g_exit_code = ft_atoi(cmd->args[1]);
		return (2);
	}
	while (builtins[i])
	{
		if (!ft_strcmp(builtins[i++], cmd->cmd))
		{
			if (cmd->is_pipe && open_pipe(cmd))
				return (error_int("pipe command failed\n", 0));
			if (!fork())
				exec_builtin(cmd, envp, envl, i - 1);
			g_exit_code = watch_child();
			clean_redirects(cmd);
			return (true);
		}
	}
	return (false);
}
