/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:36:31 by nmolinel          #+#    #+#             */
/*   Updated: 2022/12/18 12:42:32 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

t_env	*env_dup(t_env *old)
{
	t_env	*new;
	new = env_create(old->envp->mem);
	return (new);
}

t_env	*env_free(t_env *env)
{
	if (env->envl)
		buff_free(env->envl);
	if (env->envp)
		buff_free(env->envp);
	if (env->opts)
		buff_free(env->opts);
	free(env);
	return (0);
}

t_env	*env_create(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->envl = buff_create(0);
	env->opts = buff_create(0);
	env->envp = buff_create(envp);
	if (env->envl && env->envp && env->opts)
		return (env);
	return (env_free(env));
}

/**
*	Remove a variable.
*	mode 0 envp + envl,
*	mode 1 envp only,
*	mode 2 envl only,
*	Returns env, 0 if error.
*/
t_env	*env_remove(t_env *env, char *varname, int mode)
{
	t_buffvar	*buff;
	int			index;

	buff = env->envp;
	if (mode == 2)
		buff = env->envl;
	index = buff_contains(buff, varname, 0);
	if (index < 0 && mode)
		return (env);
	else if (index < 0)
		return (env_remove(env, varname, 2));
	free(buff->mem[index]);
	while (index < buff->index)
	{
		buff->mem[index] = buff->mem[index + 1];
		index++;
	}
	buff->mem[--buff->index] = 0;
	if (!mode)
		env_remove(env, varname, 2);
	return (env);
}

/**
* Add new variable or edit one that already exists.
*	mode 1 envp only,
*	mode 2 envl only,
*	Returns env, 0 if error.
*/
t_env	*env_add(t_env *env, char *var, int mode)
{
	t_buffvar	*buff;
	int			index;
	char		**split;
	char		*dup;

	buff = env->envp;
	if (mode == 2)
		buff = env->envl;
	split = sk_split(var, "=");
	if (!split)
		return (0);
	index = buff_contains(buff, split[0], 0);
	free2d(split, 0);
	dup = sk_strdup(var);
	if (!dup)
		return (0);
	if (!add_var(buff, dup, index))
		return (0);
	return (env);
}

/**
*	mode 1 envp only
*	mode 2 envl only
*	mode 0 both
*	Returns value of variable, 0 if error
*/
char	*env_get(t_env *env, char *name, int mode)
{
	t_buffvar	*buff;
	size_t		n;
	int			i;
	char		*out;

	buff = env->envp;
	if (mode == 2)
		buff = env->envl;
	i = buff_contains(buff, name, &n);
	if (i >= 0)
		return (copy_var(buff->mem[i] + n));
	if (!mode)
	{
		buff = env->envl;
		i = buff_contains(buff, name, &n);
		if (i >= 0)
			return (copy_var(buff->mem[i] + n));
	}
	out = malloc(sizeof(char));
	if (out)
		*out = 0;
	return (out);
}
