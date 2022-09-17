/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:03 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/09/17 16:34:03 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

char	*build_var(char *name, char *value)
{
	char	*var;
	size_t	size;

	size = ft_strlen(name) + ft_strlen(value) + 2;
	var = malloc(sizeof(char) * size);
	if (!var)
		return (0);
	ft_strlcpy(var, name, size);
	ft_strlcat(var, "=", size);
	ft_strlcat(var, value, size);
	return (var);
}

int	update_pwd(t_env *env, char *old_path, char *new_path)
{
	char	*new_pwd;
	char	*old_pwd;
	int		code;

	code = 137;
	old_pwd = build_var("OLDPWD", old_path);
	new_pwd = build_var("PWD", new_path);
	if (old_pwd && new_pwd && env_add(env, old_pwd, 1) \
	&& env_add(env, new_pwd, 1))
		code = 0;
	if (old_pwd)
		free(old_pwd);
	if (new_pwd)
		free(new_pwd);
	return (code);
}

int	chdir_wrapper(t_env *env, char *path)
{
	char	*pwd;
	char	*new_path;
	int		code;

	if (chdir(path) == -1)
		return (1);
	code = 137;
	pwd = env_get(env, "PWD", 1);
	if (!pwd)
		return (code);
	new_path = getcwd(0, 0);
	if (!new_path)
	{
		free(pwd);
		return (1);// get real error
	}
	code = update_pwd(env, pwd, new_path);
	free(pwd);
	free(new_path);
	return (code);
}

int	ft_cd(char **args, t_env *env)
{
	char	*home;

	if (!args[1])
	{
		home = env_get(env, "HOME", 0);
		if (!home)
			return (137);
		return (chdir_wrapper(env, home));
	}
	return (chdir_wrapper(env, args[1]));
}
