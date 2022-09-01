/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 22:44:04 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/01 18:29:23 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <termios.h>

static void	exec_signal_handler(int code)
{
	if (code == SIGINT)
		ft_printf("\n");
	else if (code == SIGQUIT)
		ft_printf("Quit\n");
	return ;
}

static void	def_signal_handler(int code)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) code;
	return ;
}

//	mode is 0 for default, 1 for exec
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
		signal(SIGINT, exec_signal_handler);
		signal(SIGQUIT, exec_signal_handler);
	}
	return (0);
}
