/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 01:26:56 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/17 01:30:39 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*error_msg(char *msg)
{
	printf("%s\n", msg);
	return (0);
}

int	error_int(char *msg, int exit_code)
{
	if (msg)
		printf("%s\n", msg);
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
