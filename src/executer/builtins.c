/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 02:24:53 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/11/02 17:38:58 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

int	ft_alias(t_cmd *cmd, t_data *data)
{
	int		i = 1;

	if (!cmd->args[1])
		return (ft_env(0, data->aliases));
	if (!strchr(cmd->args[1], '='))
	{
		char	*buff = env_get(data->aliases, cmd->args[1], 1);
		if (!buff || !*buff)
		{
			free(buff);
			return (error_int(0, 0, 1, true));
		}
		ft_printf("alias %s='%s'", cmd->args[1], buff);
		free(buff);
		return (false);
	}
	while (cmd->args[i])
		data->aliases = env_add(data->aliases, cmd->args[i++], 1);
	return (false);
}

void	exec_builtin(t_cmd *cmd, t_env *envs, int i)
{
	pid_t		pid;
	static int	(*funcs[])(char **args, t_env *env) = {
		&ft_cd, &ft_echo, &ft_export, &ft_unset, &ft_env, &ft_pwd
	};

	pid = fork();
	if (pid)
	{
		if (pid != -1)
			watch_child(pid);
		else
			error_int("Error forking process", cmd->cmd, 1, 0);
		return ;
	}
	if (cmd->is_pipe)
		close(cmd->next->redirects[0]);
	dup2(cmd->redirects[0], 0);
	dup2(cmd->redirects[1], 1);
	dup2(cmd->redirects[2], 2);
	clean_redirects(cmd);
	if (i == 6)
		ft_exit(cmd);
	g_exit_code = funcs[i](cmd->args, envs);
	exit(g_exit_code);
}

void	exec_single_builtin(t_cmd *cmd, t_env *env, int i)
{
	static int	(*funcs[])(char **args, t_env *env) = {
		&ft_cd, &ft_echo, &ft_export, &ft_unset, &ft_env, &ft_pwd
	};
	t_cmd		fds;

	fds.redirects[0] = dup(0);
	fds.redirects[1] = dup(1);
	fds.redirects[2] = dup(2);
	dup2(cmd->redirects[0], 0);
	dup2(cmd->redirects[1], 1);
	dup2(cmd->redirects[2], 2);
	if (cmd->is_pipe)
		clean_redirects(cmd);
	if (i == 6)
		ft_exit(cmd);
	g_exit_code = funcs[i](cmd->args, env);
	dup2(fds.redirects[0], 0);
	dup2(fds.redirects[1], 1);
	dup2(fds.redirects[2], 2);
	clean_redirects(&fds);
}

int	check_aliases(t_cmd *cmd, t_env *aliases)
{
	char	*substitute;
	char	**substitutes;
	char	**new_args;
	int		oglen = 0;
	int		len = 0;

	if (!cmd->cmd)
		return (false);
	substitute = env_get(aliases, cmd->cmd, 1);
	if (!substitute || !*substitute)
	{
		free(substitute);
		return (false);
	}
	substitutes = ft_split(substitute, " ");
	if (!substitutes)
		return (error_int("malloc error", "alias", 1, 0));
	while (substitutes[len++]);
	while (cmd->args[oglen++]);
	new_args = malloc((len + oglen - 1) * sizeof(char *));
	if (!new_args)
		return (error_int("malloc error", "alias", 1, 0));
	len = -1;
	while (substitutes[++len])
		new_args[len] = substitutes[len];
	oglen = 0;
	while (cmd->args[++oglen])
		new_args[len++] = cmd->args[oglen];
	new_args[len] = 0;
	free(cmd->cmd);
	free(cmd->args);
	free(substitutes);
	cmd->args = new_args;
	cmd->cmd = cmd->args[0];
	return (true);
}

int	check_builtin(t_cmd *cmd, t_data *data, int piping)
{
	int			i;
	static char	*builtins[] = {
		"cd", "echo", "export", "unset", "env", "pwd", "exit", 0
	};

	i = 0;
	if (check_aliases(cmd, data->aliases))
		return (false);
	while (builtins[i])
	{
		if (!cmd->cmd || !ft_strcmp(builtins[i], cmd->cmd))
		{
			if (cmd->is_pipe && open_pipe(cmd))
				return (error_int("Pipe opening failed\n", cmd->cmd, 1, 0));
			if (cmd->files && open_files(cmd, data))
				return (true);
			if (cmd->cmd && piping)
				exec_builtin(cmd, data->env, i);
			else if (cmd->cmd)
				exec_single_builtin(cmd, data->env, i);
			clean_redirects(cmd);
			if (i == 6 && !piping)
				return (2);
			return (true);
		}
		i++;
	}
	if (!ft_strcmp("alias", cmd->cmd))
	{
		ft_alias(cmd, data);
		return (true);
	}
	return (false);
}
