/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:16:48 by nmolinel          #+#    #+#             */
/*   Updated: 2022/11/15 16:42:56 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executer.h>

int		is_open(char c);

char	*bp(char **paths, char *cmd)
{
	return (build_path(*paths - 1, cmd - 1, \
	sk_strlen(*paths) + sk_strlen(cmd) + 2));
}

int	parent_behaviour(t_cmd *start, t_data *data, pid_t child_pid)
{
	if (child_pid == -1)
		return (error_int("Error forking process", start->cmd, 1, 1));
	if (start->next && start->next->conditional != -1)
	{
		watch_child(child_pid);
		if (!reset_path(data))
			error_int("Error allocating new PATH", start->cmd, 1, 0);
	}
	return (0);
}

char	*remove_quotes_pt2(char *p, int i)
{
	if (is_open(0))
		is_open(-1);
	if (p)
		p[i] = 0;
	return (p);
}
