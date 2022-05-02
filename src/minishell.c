/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:20:31 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/02 15:54:25 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_handler(int code)
{
	if (code == 2) //SIGINT
	{
		dprintf(2, "\b\b  ");	//\n\e[31;1mskiru ~>\e[0m");
		printf("\n"); // Move to a new line
		// rl_on_new_line(); // Regenerate the prompt on a newline
		// rl_replace_line("", 0); // Clear the previous text
		// rl_redisplay();
	}
	return ;
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
		buffer = readline("\e[31;1mskiru ~>\e[0m");
		if (!buffer)
			break ;
		if (*buffer)
			add_history(buffer);
	}
	ft_dprintf(2, "\b\b exit\n");
	exit(0);
}
