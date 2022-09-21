/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 18:20:31 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/09/12 01:15:52 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int	g_exit_code;

int	semicolon_handle(char *buffer, t_env *env)
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
		data = (t_data){0, 0, 0, 0, 0, env};
		code = lexer(semi_colons_split[counter], &data);
		if (code == 1)
			ft_printf("Error\n");
		if (code == ERROR || code == 2)// env_free?
			break ;
		counter++;
	}
	free2d(semi_colons_split, 0);
	return (code);
}

void	error_handle(char **buffer, int code)
{
	// if (code == ERROR)
		// ft_dprintf(2, "Shell error: malloc() failed\n");
	free(*buffer);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	int		code;
	t_env	*env;

	signals_handler_setup(0);
	rl_outstream = stderr;
	(void)argv;
	(void)argc;
	env = env_setup(envp);
	if (!env)
		return (44);//handle error
	while (1)
	{
		buffer = readline(TITLE);
		if (!buffer)
			break ;
		code = semicolon_handle(buffer, env);
		error_handle(&buffer, code);
		if (code == 2)
			break ;
	}
	env_free(env);
	if (code != 2)
		ft_dprintf(2, "exit\n");
	exit(g_exit_code);
}
