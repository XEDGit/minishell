/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 18:36:19 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/07 21:19:42 by xed           ########   odam.nl         */
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
		return (error_msg("malloc fail in path builder"));
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
			return (error_int("File or folder not found", false));
		return (false);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		g_exit_code = 126;
		ft_printf("'%s' is a directory", path);
		return (true);
	}
	if (S_ISREG(statbuf.st_mode) && access(path, X_OK))
	{
		g_exit_code = 126;
		return (error_int("User doesn't \
have permissions to execute", true));
	}
	return (true);
}

char	*check_paths(char **paths, char *cmd)
{
	char	*res_path;

	if (ft_strchr(cmd, '/'))
	{
		if (check_file(cmd, true) == true)
			return (cmd);
		else
		{
			free(cmd);
			return (false);
		}
	}
	while (paths && *paths)
	{
		res_path = build_path(*paths - 1, cmd - 1, \
			ft_strlen(*paths) + ft_strlen(cmd) + 2);
		if (!res_path || check_file(res_path, false) == true)
		{
			free(cmd);
			return (res_path);
		}
		free(res_path);
		paths++;
	}
	if (!ft_strchr(cmd, '/'))
		ft_dprintf(2, "%s: command not found\n", cmd);
	free(cmd);
	return (0);
}

int	open_pipe(t_cmd *cmd)
{
	int	p[2];

	if (pipe(p) == -1)
		exit(error_int("Error: pipe opening failed\n", 1));
	if (cmd->redirects[1] == 1)
		cmd->redirects[1] = p[1];
	else
	{
		if (close(p[1]) == -1 || close(p[0]) == -1)
			return (error_int("Error: pipe closing failed\n", 1));
		return (0);
	}
	if (cmd->next->redirects[0] == 0)
		cmd->next->redirects[0] = p[0];
	else if (close(p[0]) == -1)
		return (error_int("Error: pipe closing failed\n", 1));
	return (0);
}

int	clean_redirects(t_cmd *cmd)
{
	int	err;

	err = 0;
	if (cmd->redirects[0] != 0)
	{
		err += close(cmd->redirects[0]);
		cmd->redirects[0] = -1;
	}
	if (cmd->redirects[1] != 1)
	{
		err += close(cmd->redirects[1]);
		cmd->redirects[1] = -1;
	}
	if (cmd->redirects[2] != 2)
	{
		err += close(cmd->redirects[2]);
		cmd->redirects[2] = -1;
	}
	if (err)
		return (error_int("Error: pipe cleanup failed\n", 1));
	return (0);
}
