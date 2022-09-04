/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 03:04:17 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/04 05:42:55 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	ft_cd(char **args)
{
	// edit_variable("PWD", args[1]);
	chdir(args[1]);
}

void	ft_echo(char **args)
{
	int	start;

	start = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
		start++;
	args = &args[start + 1];
	while (args && *args)
		ft_printf("%s", *args++);
	ft_printf("\n");
}

void	ft_env(char **args)
{
	
}
