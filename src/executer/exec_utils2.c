/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:36:19 by lmuzio            #+#    #+#             */
/*   Updated: 2022/12/18 10:56:40 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

void	watch_child(pid_t pid)
{
	int	statbuf;

	if (waitpid(pid, &statbuf, 0) != pid)
		return ;
	if (WIFSIGNALED(statbuf))
	{
		g_exit_code = WTERMSIG(statbuf) + 128;
		if (g_exit_code == 130)
			sk_dprintf(2, "\n");
		else if (g_exit_code == 131)
			sk_dprintf(2, "Quit: 3\n");
	}
	else if (WIFEXITED(statbuf))
		g_exit_code = WEXITSTATUS(statbuf);
	while (wait(0) != -1)
		;
}

int	set_output_fd(t_cmd *cmd, t_file *files)
{
	if (cmd->redirects[files->dest] != files->dest)
	{
		if (close(cmd->redirects[files->dest]) == ERROR)
			return (error_int("Close file descriptor error", files->name, 1, 0));
	}
	cmd->redirects[files->dest] = open(files->name, files->flags, files->mode);
	if (cmd->redirects[files->dest] == ERROR)
		return (error_int("Open file descriptor error", files->name, 1, 0));
	return (1);
}

int	left_rdrt(t_cmd *cmd, char *file, int mode)
{
	if (cmd->redirects[0] != STDIN_FILENO)
	{
		if (close(cmd->redirects[0]) == ERROR)
			return (error_int("Open error", file, 1, false));
	}
	cmd->redirects[0] = open(file, mode);
	if (cmd->redirects[0] == ERROR)
		return (error_int("Open error", file, 1, false));
	return (1);
}

int	reset_path(t_data *data)
{
	char	*new_paths;

	new_paths = env_get(data->env, "PATH", 1);
	if (!new_paths)
		return (false);
	free2d(data->paths, 0);
	data->paths = sk_split(new_paths, ":");
	free(new_paths);
	if (!data->paths)
		return (false);
	return (true);
}

int	open_files(t_cmd *cmd, t_data *data)
{
	t_file	*files;

	files = cmd->files;
	while (files)
	{
		if (files->here == 1)
			cmd->redirects[0] = data->heredocs[data->heredoc_c++][0];
		else if (!files->flags && !left_rdrt(cmd, files->name, files->mode))
			return (true);
		else if (files->flags && \
		!set_output_fd(cmd, files))
			return (true);
		files = files->next;
	}
	return (false);
}
