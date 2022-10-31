/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 22:44:04 by lmuzio            #+#    #+#             */
/*   Updated: 2022/10/31 15:28:04 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <termios.h>

static void	def_signal_handler(int code)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) code;
	return ;
}

//	mode is 0 for default, 1 for exec, 2 for ignore everything
int	signals_handler_setup(int mode)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	if (mode == 0)
	{
		signal(SIGINT, def_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return (0);
}
