/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmolinel <nmolinel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 01:26:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/11/02 15:30:43 by nmolinel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

void	*error_msg(char *msg, int exit_code)
{
	ft_dprintf(2, SHELLNAME"%s\n", msg);
	if (exit_code != -1)
		g_exit_code = exit_code;
	return (0);
}

/*
If cmd and msg are not null "*SHELLNAME*: *cmd*: *msg*\n" will be printed.
if msg is not null "*SHELLNAME*: *msg*\n" will be printed.
if exit_code is not -1 it will be set as g_exit_code.
return_val is always returned
*/
int	error_int(char *msg, char *cmd, int exit_code, int return_val)
{
	if (msg)
	{
		if (cmd)
			ft_dprintf(2, SHELLNAME"%s: %s\n", cmd, msg);
		else
			ft_dprintf(2, SHELLNAME"%s\n", msg);
	}
	if (exit_code != ERROR)
		g_exit_code = exit_code;
	return (return_val);
}

int	error_free(void *tofree)
{
	free(tofree);
	return (1);
}

int	error_free2dint(void *tofree, int len, int ret)
{
	free2dint(tofree, len);
	return (ret);
}

int	error_free2d(void *tofree)
{
	free2d(tofree, 0);
	return (1);
}
