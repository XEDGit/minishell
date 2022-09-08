/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 02:24:53 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/04 03:50:16 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

int	check_builtin(t_cmd *cmd)
{
	int			i;
	static char	*builtins[] = {
		"cd", "echo", "export", "unset", "env", "pwd", 0
	};
	static void	(*funcs[])(char **args) = {
		&ft_cd, &ft_echo, &ft_export, &ft_unset, &ft_env, &ft_pwd
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
			funcs[i - 1](cmd->args);
			return (true);
		}
	}
	return (false);
}
