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

#include <shared.h>

#define EXPDEC "declare -x "

int	get_arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	print_lowest_ascii(char **mem)
{
	int		i;
	int		s;
	int		m;
	char	*pos;

	m = 0;
	i = 1;
	while (mem[i])
	{
		s = 0;
		while (mem[i][s] && mem[m][s] && mem[i][s] == mem[m][s])
			s++;
		if (mem[i][s] < mem[m][s])
			m = i;
		i++;
	}
	pos = ft_strchr(mem[m], '=');
	if (!pos)
		ft_printf("%s%s\n", EXPDEC, mem[m]);
	else
	{
		*pos++ = 0;
		ft_printf("%s%s=\"%s\"\n", EXPDEC, mem[m], pos);
	}
	return (m);
}

int	print_p(t_env *env)
{
	int			length;
	int			index;
	t_buffvar	*cp;

	cp = buff_create(env->envp->mem);
	if (!cp)
		return (137);
	length = get_arr_length(env->envp->mem);
	while (length--)
	{
		index = print_lowest_ascii(env->envp->mem);
		env_remove(env, env->envp->mem[index], 1);
	}
	buff_free(env->envp);
	env->envp = cp;
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
		if (ft_isdigit(**args))
		{
			error_int("variable starting with digit are not allowed", "export", 1, 0);
			args++;
			continue ;
		}
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
