/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:20:31 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/02 17:29:31 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_handler(int code)
{
	if (code == SIGINT)
	{
		printf("\33[2K");
	    rl_on_new_line();
	    rl_redisplay();
		printf("\n");
	    rl_on_new_line();
	    rl_replace_line("", 0);
	    rl_redisplay();
	}
	return ;
}

int	signals_handler_setup(void)
{
	signal(2, signals_handler);
	signal(3, 0);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	int		error_code;

	signals_handler_setup();
	ft_printf("%d\n", getpid());
	while (1)
	{
		buffer = readline("\e[31;1mskiru ~> \e[0m");
		if (!buffer)
			break ;
		if (*buffer)
			add_history(buffer);
	}
	ft_dprintf(2, " exit\n");
	exit(0);
}
