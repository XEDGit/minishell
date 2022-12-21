/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sk_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 16:34:17 by nmolinel      #+#    #+#                 */
/*   Updated: 2022/11/01 18:04:35 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	sk_env(t_cmd *cmd, t_data *data)
{
	int		i;
	char	newline = '\n', **envp;

	(void)cmd;
	i = 1;
	t_env	*enviroment = env_dup(data->env);
	if (!enviroment)
		return (error_int("error creating enviroment", "env", -1, 1));
	if (cmd->args[i])
	{
		char	*arg;
		while ((arg = cmd->args[i++]) && *arg == '-')
		{
			if (!sk_strcmp(arg, "-i") || !sk_strcmp(arg, "--ignore-enviroment"))
			{
				env_free(enviroment);
				enviroment = env_create((char **){0});
				if (!enviroment)
					return (error_int("error creating enviroment", "env", -1, 1));
			}
			else if (!sk_strncmp(arg, "-u", 2) || !sk_strncmp(arg, "--unset", 7))
				env_remove(enviroment, cmd->args[i], 0);
			else if (!sk_strncmp(arg, "-0", 2) || !sk_strncmp(arg, "--null", 6))
				newline = '\0';
			else
			{
				sk_dprintf(2, SHELLNAME"env: argument '%s' is not a flag\n", arg);
				return (1);
			}
		}
		i--;
		while ((arg = cmd->args[i++]) && sk_strchr(arg, '='))
			if (!env_add(enviroment, arg, 1))
			{
				env_free(enviroment);
				return (error_int("error creating enviroment", "env", -1, 1));
			}
		i--;
		if (cmd->args[i])
		{
			char	*input = 0;
			while (cmd->args[i])
				if (sk_strjoin(&input, cmd->args[i++], false) || sk_strjoin(&input, " ", false))
				{
					free(input);
					return (error_int("error creating enviroment", "env", -1, 1));
				}
			sk_subshell(input, enviroment, data->aliases, true, false);
			env_free(enviroment);
			free(input);
			return (0);
		}
	}
	i = 0;
	envp = enviroment->envp->mem;
	while (envp[i])
	{
		if (sk_strchr(envp[i], '='))
			sk_printf("%s%c", envp[i], newline);
		i++;
	}
	env_free(enviroment);
	return (0);
}
