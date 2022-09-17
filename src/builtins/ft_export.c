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
#include <ft_libc.h>
#include <unistd.h>
#include <ft_printf.h>

#define EXPDEC "declare -x "

int	get_arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

// Mi cacciano da codam
// int	print_p(t_env *env)
// {
// 	int		i;
// 	int		s;
// 	int		m;
// 	int		length;
// 	size_t	pos;
// 	t_buffvar	*cp;

// 	cp = buff_create(env->envp->mem);
// 	if (!cp)
// 		return (137);
// 	length = get_arr_length(env->envp->mem);
// 	while (length--)
// 	{
// 		m = 0;
// 		i = 1;
// 		s = 0;
// 		while (env->envp->mem[i])
// 		{
// 			while (env->envp->mem[i][s] && env->envp->mem[m][s] && env->envp->mem[i][s] == env->envp->mem[m][s])
// 				s++;
// 			if (env->envp->mem[i][s] < env->envp->mem[m][s])
// 				m = i;
// 			i++;
// 		}
// 		pos = ft_strchr(env->envp->mem[m], '=') -  env->envp->mem[m];
// 		env->envp->mem[m][pos] = 0;
// 		ft_printf("%s%s=\"%s\"\n", EXPDEC, env->envp->mem[m], env->envp->mem[m] + pos + 1);
// 		env_remove(env, env->envp->mem[m], 1);
// 	}
// 	buff_free(env->envp);
// 	env->envp = cp;
// 	return (0);
// }

int	ft_export(char **args, t_env *env)
{
	int		index;
	char	*to_add;

	// if (!*(++args))
	// 	return (print_p(env));
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
