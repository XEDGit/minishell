/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 03:04:17 by lmuzio            #+#    #+#             */
/*   Updated: 2022/09/12 20:10:22 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

int	ft_cd(char **args, t_env *env)
{
	// env_add("OLD_PWD", ft_get_variable("PWD", envp));
	// ft_edit_variable("PWD", args[1]);
	if (args[1] && chdir(args[1]) == -1)
		return (1);
	return (0);
}

int	ft_echo(char **args, t_env *env)
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
		ft_printf("%s", args[i]);
		if (i++)
			ft_printf(" ");
	}
	if (!start)
		ft_printf("\n");
	return (0);
}

int	ft_env(char **args, t_env *env)
{
	char	**envp;

	envp = env->envp->mem;
	while (envp && *envp)
		ft_printf("%s\n", *envp++);
	return (0);
}
