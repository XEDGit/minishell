#include <shared.h>

int	ft_unset(char **args, t_env *env)
{
	while (++args && *args)
		env_remove (env, *args, 0);
	return (0);
}

int	print_p(t_env *env)
{
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	int 	index;
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

int	ft_pwd(char **args, t_env *env)
{
	return (0);
}