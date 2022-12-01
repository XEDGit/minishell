/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sk_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:23 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/11/02 16:05:06 by nmolinel      ########   odam.nl         */
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
	pos = sk_strchr(mem[m], '=');
	if (!pos)
		sk_printf("%s%s\n", EXPDEC, mem[m]);
	else
	{
		*pos++ = 0;
		sk_printf("%s%s=\"%s\"\n", EXPDEC, mem[m], pos);
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

int	sk_export(t_cmd *cmd, t_data *data)
{
	int		index;
	int		ret;
	char	*to_add;
	char	**args;

	args = cmd->args;
	if (!*(++args))
		return (print_p(data->env));
	ret = 0;
	while (args && *args)
	{
		if (!valid_varname(*args))
		{
			ret = error_int(VARIDERR, "export", 1, 1);
			args++;
			continue ;
		}
		index = buff_contains(data->env->envl, *args, 0);
		if (index > -1)
			to_add = data->env->envl->mem[index];
		else
			to_add = *args;
		if (!env_add(data->env, to_add, 1))
			return (137);
		args++;
	}
	return (ret);
}
