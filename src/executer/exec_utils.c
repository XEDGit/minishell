/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 18:36:19 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/02 18:40:44 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

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
		exit(error_int("Error: pipe cleanup failed\n", 1));
	return ;
}