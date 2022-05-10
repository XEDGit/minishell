/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 18:20:31 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/10 23:04:58 by lmuzio        ########   odam.nl         */
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
		count = -1;
		buffer = readline(TITLE);
		if (!buffer || lexer(buffer))
			break ;
		free(buffer);
	}
	ft_dprintf(2, " exit\n");
	exit(0);
}
