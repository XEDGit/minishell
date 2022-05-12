/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:20:31 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/12 18:54:15 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	int		code;

	signals_handler_setup();
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		buffer = readline(TITLE);
		if (!buffer)
			break ;
		code = lexer(buffer);
		if (code == ERROR)
			break ;
		if (code)
			ft_printf("Error\n");
		free(buffer);
	}
	ft_dprintf(2, " exit\n");
	exit(0);
}
