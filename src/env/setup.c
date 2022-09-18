#include <env.h>
#include <ft_libc.h>

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

static t_env	*set_shlvl(t_env *env)
{
	size_t	n;
	char	*var;
	int		index;

	index = buff_contains(env->envp, "SHLVL", &n);
	if (index == -1 || !env->envp->mem[index][n])
	{
		var = build_var("SHLVL", "1");
		if (!var)
			return (0);
		if (!env_add(env, var, 1))
		{
			free(var);
			return (0);
		}
		free(var);
	}
	else if (!increment_shlvl(env, index, n))
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
	if (set_oldpwd(env) && set_shlvl(env))
		return (env);
	return (env_free(env));
}