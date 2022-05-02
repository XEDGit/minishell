/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:20:31 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/02 23:40:05 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	char	**buffer_pipes;
	int		count;
	int		error_code;

	signals_handler_setup();
	while (1)
	{
		buffer = readline("\e[31;1mskiru ~> \e[0m");
		if (!buffer)
			break ;
		if (*buffer)
			add_history(buffer);
		buffer_pipes = ft_split(buffer, '|');
		count = 0;
		if (buffer_pipes)
			while (buffer_pipes[count])
				ft_printf("%s\n", buffer_pipes[count++]);
		free2d(buffer_pipes, count);
		free(buffer);
	}
	ft_dprintf(2, " exit\n");
	exit(0);
}
