/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sk_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:34:03 by nmolinel          #+#    #+#             */
/*   Updated: 2022/11/15 15:19:37 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

char	*build_var(char *name, char *value)
{
	char	*var;
	size_t	size;

	size = sk_strlen(name) + sk_strlen(value) + 2;
	var = malloc(sizeof(char) * size);
	if (!var)
		return (0);
	sk_strlcpy(var, name, size);
	sk_strlcat(var, "=", size);
	sk_strlcat(var, value, size);
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

int	chdir_wrapper(t_env *env, char *p)
{
	char	*pwd;
	char	*new_path;
	int		code;

	if (chdir(p) == -1)
		return (error_int("directory not found", "cd", 1, 1));
	pwd = env_get(env, "PWD", 1);
	if (!pwd)
		return (137);
	new_path = getcwd(0, 0);
	if (!new_path)
	{
		if ((*p != '/' && sk_strjoin(&pwd, "/", 0)) || sk_strjoin(&pwd, p, 1))
			error_int("malloc fail", "cd", -1, 0);
		new_path = build_var("PWD", pwd);
		env_add(env, new_path, 1);
		free(new_path);
		free(pwd);
		return (error_int("getcwd: error retrieving current directory", \
		"cd", 0, 0));
	}
	code = update_pwd(env, pwd, new_path);
	free(pwd);
	free(new_path);
	return (code);
}

int	sk_cd(t_cmd *cmd, t_data *data)
{
	char	*home;
	int		code;

	if (!cmd->args[1])
	{
		home = env_get(data->env, "HOME", 0);
		if (!home)
			return (137);
		else if (!*home)
			return (0);
		code = chdir_wrapper(data->env, home);
		free(home);
		return (code);
	}
	return (chdir_wrapper(data->env, cmd->args[1]));
}
