#include <ft_libc.h>
#include <unistd.h>
#include <env.h>

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
*	mode 0 both
*	mode 1 envp only
*	mode 2 envl only
*	Returns 0 on error or value of variable
*/
char	*ft_get_env(t_env *env, char *name, int mode)
{
	t_buffvar	*buff;

	buff = env->envp;
	if (mode == 2)
		buff = env->envl;
	while (i < buff->index)
	{
		n = ft_strchr(buff->mem[i], '=') - buff->mem[i];
		if (!ft_strncmp(buff->mem[i], name, n))
		{
			n++;
			out = malloc(sizeof(char) * ft_strlen(buff->mem[i] + n) + 1);
			if (out)
				ft_strlcpy(out, buff->mem[i] + n, ft_strlen(buff->mem[i] + n) + 1);
			return (out);
		}
		i++;
	}
	if (mode == 1 || mode == 2)
	{
		out = malloc(sizeof(char));
		if (out)
			*out = 0;
		return (out);
	}
	i = 0;
	buff = env->envl;
	while (i < buff->index)
	{
		n = ft_strchr(buff->mem[i], '=') - buff->mem[i];
		if (!ft_strncmp(buff->mem[i], name, n))
		{
			n++;
			out = malloc(sizeof(char) * ft_strlen(buff->mem[i] + n) + 1);
			if (out)
				ft_strlcpy(out, buff->mem[i] + n, ft_strlen(buff->mem[i] + n) + 1);
			return (out);
		}
		i++;
	}
	out = malloc(sizeof(char));
	if (out)
		*out = 0;
	return (out);
}
