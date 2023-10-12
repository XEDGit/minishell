/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:36:19 by lmuzio            #+#    #+#             */
/*   Updated: 2022/11/24 17:34:49 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

char	*build_path(char *temp_path, char *temp_cmd, int len)
{
	char		*res_path;
	int			c;

	c = 0;
	res_path = malloc(len);
	if (!res_path)
		return (error_msg("Malloc fail in path builder", -1));
	while (*++temp_path)
		res_path[c++] = *temp_path;
	res_path[c++] = '/';
	while (*++temp_cmd)
		res_path[c++] = *temp_cmd;
	res_path[c] = 0;
	return (res_path);
}

int	check_file(char *path, int initial)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	if (access(path, F_OK))
	{
		if (initial)
			return (error_int("file or folder not found", path, 127, false));
		return (false);
	}
	if (S_ISDIR(statbuf.st_mode))
		return (error_int("is a directory", path, 126, false));
	if (S_ISREG(statbuf.st_mode) && access(path, X_OK))
		return (error_int("user doesn't have permissions to execute", path, 126, false));
	return (true);
}

char	*check_paths(char **paths, char *cmd)
{
	char	*res_path;

	if (!*cmd || !sk_strcmp(cmd, ".") || !sk_strcmp(cmd, ".."))
		return ((char *)(long) error_int("command not found", cmd, 2, 0));
	if (sk_strchr(cmd, '/'))
	{
		if (check_file(cmd, true) == true)
			return (cmd);
		return (false);
	}
	while (paths && *paths)
	{
		res_path = bp(paths, cmd);
		if (!res_path || check_file(res_path, false) == true)
		{
			if (res_path)
				free(cmd);
			return (res_path);
		}
		free(res_path);
		paths++;
	}
	if (!sk_strchr(cmd, '/'))
		error_int("command not found", cmd, 127, 0);
	return (0);
}

int	open_pipe(t_cmd *cmd)
{
	int	p[2];

	if (pipe(p) == -1)
		exit(error_int("error: pipe opening failed\n", cmd->cmd, 1, 1));
	if (cmd->redirects[1] == 1)
		cmd->redirects[1] = p[1];
	else
	{
		if (close(p[1]) == -1 || close(p[0]) == -1)
			return (error_int("error: pipe closing failed\n", cmd->cmd, 1, 1));
		return (0);
	}
	if (cmd->next->redirects[0] == 0)
		cmd->next->redirects[0] = p[0];
	else if (close(p[0]) == -1)
		return (error_int("error: pipe closing failed\n", cmd->cmd, 1, 1));
	return (0);
}

int	clean_redirects(t_cmd *cmd)
{
	int	err;

	err = 0;
	if (cmd->redirects[0] != 0 && close(cmd->redirects[0]))
		err += error_int("failed closing input file descriptor\n", 0, 1, 1);
	if (cmd->redirects[1] != 1 && close(cmd->redirects[1]))
		err += error_int("failed closing output file descriptor\n", 0, 1, 1);
	if (cmd->redirects[2] != 2 && close(cmd->redirects[2]))
		err += error_int("failed closing error file descriptor\n", 0, 1, 1);
	if (err)
		return (1);
	return (0);
}
