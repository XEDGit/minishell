/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:20:31 by lmuzio            #+#    #+#             */
/*   Updated: 2022/04/25 20:51:29 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "printf/ft_printf.h"

void	signals_handler(int code)
{
	if (code == 2)
		ft_printf("\b\b  \n\e[31;1mskiru ~>\e[0m");
}

int	signals_handler_setup(void)
{
	signal(2, signals_handler);
	signal(3, signals_handler);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	int		error_code;

	signals_handler_setup();
	while (1)
	{
		ft_printf("\e[31;1mskiru ~>\e[0m");
		buffer = readline(0);
		if (!buffer)
		{
			error_code = 1;
			break ;
		}
		if (*buffer)
			add_history(buffer);
	}
	ft_dprintf(2, "\b\b  \nError: %d\n", error_code);
	exit(1);
}
