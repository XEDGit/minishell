/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 03:04:17 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/07 21:48:46 by xed           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

int	ft_cd(char **args, char **envp, char **envl)
{
	// edit_variable("PWD", args[1]);
	chdir(args[1]);
	return (0);
}

int	ft_echo(char **args, char **envp, char **envl)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	if (args[1] && args[1][i++] == '-')
	{
		while (args[1][i] == 'n')
			i++;
		if (!args[1][i])
			start++;
	}
	i = 0;
	args = &args[start + 1];
	while (args && args[i])
	{
		ft_printf("%s", args[i++]);
		if (i)
			ft_printf(" ");
	}
	if (!start)
	ft_printf("\n");
	return (0);
}

int	ft_env(char **args, char **envp, char **envl)
{
	while (envp && *envp)
		ft_printf("%s\n", *envp++);
	return (0);
}
