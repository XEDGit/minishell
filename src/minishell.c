/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:20:31 by lmuzio            #+#    #+#             */
/*   Updated: 2022/05/04 21:18:45 by lmuzio           ###   ########.fr       */
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
		count = 0;
		buffer = readline("\e[31;1mskiru ~> \e[0m");
		if (!buffer)
			break ;
		if (*buffer)
			add_history(buffer);
		buffer_pipes = ft_split(buffer, "|&");
		while (buffer_pipes[count])
			printf("split[%d]: %s\n", count, buffer_pipes[count++]);
		free2d(buffer_pipes, count);
		free(buffer);
	}
	ft_dprintf(2, " exit\n");
	exit(0);
}
