#include <shared.h>

t_env	*env_free(t_env *env)
{
	if (env->envl)
		buff_free(env->envl);
	if (env->envp)
		buff_free(env->envp);
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
	env->envp = buff_create(envp);
	if (env->envl && env->envp)
		return (env);
	return (env_free(env));
}

/**
*	Remove a variable.
*	mode 1 envp only,
*	mode 2 envl only,
*	Returns env, 0 if error.
*/
t_env	*env_remove(t_env *env, char *var, int mode)
{
	t_buffvar	*buff;
	int			index;
	char 		**split;
	char		*dup;

	buff = env->envp;
	if (mode == 2)
		buff = env->envl;
	split = ft_split(var, "=");
	if (!split)
		return (0);
	index = buff_contains(buff, split[0], 0);
	free2d(split, 0);
	if (index < 0)
		return (env);
	free(buff->mem[index]);
	while (index < buff->index)
	{
		buff->mem[index] = buff->mem[index + 1];
		index++;
	}
	buff->index--;
	return (env);
}

/**
* Add new variable or edit one that already exixsts.
*	mode 1 envp only,
*	mode 2 envl only,
*	Returns env, 0 if error.
*/
t_env	*env_add(t_env *env, char *var, int mode)
{
	t_buffvar	*buff;
	int			index;
	char 		**split;
	char		*dup;


	buff = env->envp;
	if (mode == 2)
		buff = env->envl;
	if (!buff_checker(buff))// TO TEST
		return (0);
	split = ft_split(var, "=");
	if (!split)
		return (0);
	index = buff_contains(buff, split[0], 0);
	free2d(split, 0);
	dup = ft_strdup(var);
	if (!dup)
		return (0);
	if (index >= 0)
	{
		free(buff->mem[index]);
		buff->mem[index] = dup;
	}
	else
		buff->mem[buff->index++] = dup;
	return (env);
}

/**
*	mode 0 both
*	mode 1 envp only
*	mode 2 envl only
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
	{
		out = malloc(sizeof(char) * ft_strlen(buff->mem[i] + n) + 1);
		if (out)
			ft_strlcpy(out, buff->mem[i] + n, ft_strlen(buff->mem[i] + n) + 1);
		return (out);
	}
	if (!mode)
	{
		buff = env->envl;
		i = buff_contains(buff, name, &n);
		if (i >= 0)
		{
			out = malloc(sizeof(char) * ft_strlen(buff->mem[i] + n) + 1);
			if (out)
				ft_strlcpy(out, buff->mem[i] + n, ft_strlen(buff->mem[i] + n) + 1);
			return (out);
		}
	}
	out = malloc(sizeof(char));
	if (out)
		*out = 0;
	return (out);
}
