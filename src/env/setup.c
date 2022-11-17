/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:38:46 by nmolinel          #+#    #+#             */
/*   Updated: 2022/10/26 15:38:47 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <shared.h>

t_env	*increment_shlvl(t_env *env, int index, size_t n)
{
	int		num;
	t_env	*code;
	char	*lvl;
	char	*var;

	code = env;
	num = ft_atoi(env->envp->mem[index] + n) + 1;
	lvl = ft_itoa(num);
	if (!lvl)
		return (0);
	var = build_var("SHLVL", lvl);
	if (!var)
	{
		free(lvl);
		return (0);
	}
	if (!env_add(env, var, 1))
		code = 0;
	free(var);
	free(lvl);
	return (code);
}

t_env	*set_if_not_set(t_env *env, char *name, char *content)
{
	size_t	n;
	char	*var;
	int		index;

	index = buff_contains(env->envp, name, &n);
	if (index == -1 || !env->envp->mem[index][n])
	{
		var = build_var(name, content);
		if (!var)
			return (0);
		if (!env_add(env, var, 1))
		{
			free(var);
			return (0);
		}
		free(var);
	}
	else if (!ft_strcmp(name, "SHLVL") && !increment_shlvl(env, index, n))
		return (0);
	return (env);
}

static t_env	*set_oldpwd(t_env *env)
{
	if (!env_add(env, "OLDPWD", 1))
		return (0);
	return (env);
}

t_env	*env_setup(char **envp)
{
	t_env	*env;

	env = env_create(envp);
	if (!env)
		return (0);
	if (set_oldpwd(env) && set_if_not_set(env, "SHLVL", "1") && set_if_not_set(env, "SKU1", TITLE))
		return (env);
	return (env_free(env));
}
