/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 19:22:13 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/08/17 21:36:01 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_paths(char **paths, char *cmd)
{
	char		*res_path;
	char		*temp_path;
	char		*temp_cmd;
	int			c;
	struct stat	statbuf;

	while (*paths)
	{
		c = 0;
		temp_cmd = cmd - 1;
		temp_path = *paths - 1;
		res_path = malloc(ft_strlen(*paths) + ft_strlen(cmd) + 2);
		while (*++temp_path)
			res_path[c++] = *temp_path;
		res_path[c++] = '/';
		while (*++temp_cmd)
			res_path[c++] = *temp_cmd;
		res_path[c] = 0;
		if (!stat(res_path, &statbuf))
			return (res_path);
		free(res_path);
		paths++;
	}
	ft_dprintf(2, "%s: command not found\n", cmd);
	return (0);
}

int	executer(t_data *data)
{
	pid_t	child_pid;
	int		exit_code;

	data->paths = ft_split(getenv("PATH"), ":");
	while (data->cmds)
	{
		data->cmds->cmd = check_paths(data->paths, data->cmds->cmd);
		if (data->cmds->cmd != NULL)
		{
			child_pid = fork();
			if (!child_pid)
			{
				exit_code = execve(data->cmds->cmd, data->cmds->args, 0);
				exit(exit_code);
			}
			waitpid(-1, 0, 0);
		}
		data->cmds = data->cmds->next;
	}
	return (0);
}
