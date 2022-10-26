/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolinel <nmolinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:14:47 by nmolinel          #+#    #+#             */
/*   Updated: 2022/10/26 16:14:48 by nmolinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	is_redirect(char c)
{
	if (c == LEFT_REDIRECT)
		return (LEFT_REDIRECT);
	else if (c == RIGHT_REDIRECT)
		return (RIGHT_REDIRECT);
	return (0);
}

static int	try_redirect(char **table, t_cmd *cmd)
{
	char	*from;
	void	*red;
	t_file	*file;

	from = *table;
	file = add_file(cmd);
	if (!file)
		return (0);
	file->next = 0;
	file->mode = MODE;
	if (**table == RIGHT_REDIRECT)
		red = out_redirect(table, file);
	else if (**table == LEFT_REDIRECT)
		red = in_redirect(table, file);
	if (!red)
		return (0);
	ft_memset(from, ' ', *table - from);
	return (1);
}

int	set_redirects(char *arg, t_cmd *cmd)
{
	int		open;

	while (*arg)
	{
		open = is_open(*arg);
		if (!open && is_redirect(*arg))
		{
			if (!try_redirect(&arg, cmd))
				return (0);
			continue ;
		}
		else if (!open && *arg == '(' && ft_memset(arg, ' ', 1))
			cmd->depth++;
		else if (!open && *arg == ')' && ft_memset(arg, ' ', 1))
		{
			if (cmd->depth_next == -1)
				cmd->depth_next = cmd->depth - 1;
			else
				cmd->depth_next--;
		}
		arg++;
	}
	return (1);
}
