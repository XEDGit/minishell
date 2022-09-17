/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:23 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/09/17 16:34:23 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

#define EXPDEC "declare -x "

int	print_p(t_env *env)
{
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	int		index;
	char	*to_add;

	if (!*(++args))
		return (print_p(env));
	while (args && *args)
	{
		index = buff_contains(env->envl, *args, 0);
		if (index > -1)
			to_add = env->envl->mem[index];
		else
			to_add = *args;
		if (!env_add(env, to_add, 1))
			return (137);
		args++;
	}
	return (0);
}
