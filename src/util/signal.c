/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 22:44:04 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/08/17 21:45:38 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	signals_handler(int code)
{
	printf("\33[2K");
	rl_on_new_line();
	rl_redisplay();
	if (code == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

int	signals_handler_setup(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, signals_handler);
	return (0);
}
