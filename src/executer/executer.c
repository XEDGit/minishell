/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 19:22:13 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/01 20:09:59 by lmuzio        ########   odam.nl         */
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

void	open_pipe(t_cmd *cmd)
{
	int	p[2];

	if (pipe(p) == -1)
		exit(error_int("Error: pipe opening failed\n", 1));
	if (cmd->redirects[1] == 1)
		cmd->redirects[1] = p[1];
	else
	{
		if (close(p[1]) == -1 || close(p[0]) == -1)
			exit(error_int("Error: pipe closing failed\n", 1));
		return ;
	}
	if (cmd->next->redirects[0] == 0)
		cmd->next->redirects[0] = p[0];
	else if (close(p[0]) == -1)
		exit(error_int("Error: pipe closing failed\n", 1));
	return ;
}

void	clean_redirects(t_cmd *cmd)
{
	int	err;

	err = 0;
	if (cmd->redirects[0] != 0)
		err += close(cmd->redirects[0]);
	if (cmd->redirects[1] != 1)
		err += close(cmd->redirects[1]);
	if (cmd->redirects[2] != 2)
		err += close(cmd->redirects[2]);
	if (err)
		exit(error_int("Error: pipe cleanup failed\n", 1));
	return ;
}

int	execute_cmd(t_cmd *cmd)
{
	int	exit_code;

	dup2(cmd->redirects[0], 0);
	dup2(cmd->redirects[1], 1);
	dup2(cmd->redirects[2], 2);
	execve(cmd->cmd, cmd->args, 0);
}

int	executer(t_data *data)
{
	pid_t	child_pid;
	char	*new_cmd;

	data->paths = ft_split(getenv("PATH"), ":");
	signals_handler_setup(1);
	while (data->cmds)
	{
		new_cmd = check_paths(data->paths, data->cmds->cmd);
		if (new_cmd != NULL)
		{
			data->cmds->cmd = new_cmd;
			if (data->cmds->is_pipe)
				open_pipe(data->cmds);
			child_pid = fork();
			if (!child_pid)
				execute_cmd(data->cmds);
			clean_redirects(data->cmds);
			waitpid(-1, 0, 0); // make function to watch on child exit status
			free(data->cmds->cmd);
		}
		data->cmds = data->cmds->next;
	}
	signals_handler_setup(0);
	return (0);
}
