/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:20:31 by lmuzio            #+#    #+#             */
/*   Updated: 2022/08/01 16:14:35 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	semicolon_handle(char *buffer)
{
	char	**semi_colons_split;
	int		counter;
	int		code;
	t_data	data;

	semi_colons_split = ft_split(buffer, ";");
	if (!semi_colons_split)
		return (ERROR);
	counter = 0;
	while (semi_colons_split[counter])
	{
		data = (t_data){0, 0, 0, 0};
		code = lexer(semi_colons_split[counter], &data);
		if (code)
			ft_printf("Error\n");
		if (code == ERROR)
			break ;
		counter++;
	}
	free2d(semi_colons_split, 0);
	return (code);
}

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
		code = semicolon_handle(buffer);
		if (code == ERROR)
			printf("Error: allocation failed\n");
		free(buffer);
	}
	ft_dprintf(2, "exit\n");
	exit(0);
}
