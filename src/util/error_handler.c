/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 01:26:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/02 19:12:20 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

void	*error_msg(char *msg)
{
	ft_dprintf(2, "%s\n", msg);
	return (0);
}

int	error_int(char *msg, int exit_code)
{
	if (msg)
		ft_dprintf(2, "%s\n", msg);
	return (exit_code);
}

int	error_free(void *tofree)
{
	free(tofree);
	return (1);
}

int	error_free2dint(void *tofree)
{
	free2dint(tofree, 0);
	return (1);
}

int	error_free2d(void *tofree)
{
	free2d(tofree, 0);
	return (1);
}
